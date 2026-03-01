/// XSIO Modules
#include "xsio/virtual/worker.hpp"
#include "xsio/async/manager.hpp"

//  PUBLIC METHODS  //

void XSIO::Virtual::Worker::pause() {
    $_PP_SCOPE() {
        $_UNUSED $_AUTO = $::Lock::guard(m_mutex);
        m_paused.compare_exchange_strong(false, true);
    }

    // and attempt waiting whilst possible to do so
    for (auto now = state(); !m_safe(now);) now = m_until(now);
}

void XSIO::Virtual::Worker::resume() {
    auto lock = $::Lock::scope(m_mutex);
    m_paused.compare_exchange_strong(true, false);
    lock.unlock(), m_cv_wake.notify_one();
}

void XSIO::Virtual::Worker::checkpoint() {
    // ignore if not currently paused
    if (!m_paused) return;

    // cache the previous worker state
    auto original = m_update(state(), State::PAUSED);

    // and wait until we can start the world again
    auto lock = $::Lock::scope(m_mutex);
    m_cv_wake.wait(lock, [&] { return !m_paused; });
    lock.unlock(), m_update(State::PAUSED, original);
}

//  PRIVATE METHODS  //

void XSIO::Virtual::Worker::m_stall() {
    // declare as currently in the idle state
    m_idle.compare_exchange_strong(false, true);
    m_update(State::ACQUIRE, State::WAITING);

    auto lock = $::Lock::scope(m_mutex);  // prepare the lock to be used now
    const auto duration = m_manager->options()->worker.wait_time.underlying();
    m_cv_idle.wait_for(lock, duration, [&] { return !m_idle || !m_manager->running(); });
    m_idle.compare_exchange_strong(true, false), lock.unlock();  // declare not idle now

    // ensure we go back to the acquiring state
    m_update(State::WAITING, State::ACQUIRE);
}

void XSIO::Virtual::Worker::m_process(Async::Scheduler* scheduler) {
    Switch::yield_to_worker(this), scheduler->release(this);
}

void XSIO::Virtual::Worker::m_main() {
    // pre-wait for the context to be ready
    m_manager->ready();

    // get the scheduler instance as well
    auto* scheduler = m_manager->scheduler();
    m_update(State::CLEANED, State::ACQUIRE);

    // attempt running the worker indefinitely
    for (; m_manager->running(); m_stall()) {
        // attempt scheduling and stall if not available
        if (!scheduler->assign(this)) continue;

        m_update(State::ACQUIRE, State::WORKING);
        m_process(scheduler);  // process work now
        m_update(State::WORKING, State::ACQUIRE);
    }

    // when complete, declare as shutdown now
    m_update(State::ACQUIRE, State::SHUTDOWN);
}
