/// XSIO Includes
#include "xsio/virtual/worker.hpp"
#include "xsio/async/manager.hpp"

//  CONSTRUCTORS  //

XSIO::Virtual::Worker::Worker() : Worker($::Global::get<Async::Manager>()) {}

XSIO::Virtual::Worker::Worker(Async::Manager *runtime) : Worker(runtime, runtime->scheduler()) {}

XSIO::Virtual::Worker::Worker(Async::Manager *runtime, Async::Scheduler *scheduler) :
    Worker(runtime, scheduler->acquire<Thread>()->assign<Task::Scheduler>(runtime)) {}

XSIO::Virtual::Worker::Worker(Async::Manager *runtime, Task::Scheduler *scheduler) :
    m_scheduler(scheduler->thread()), m_runtime(runtime), m_handle(&Worker::m_main, this) {}

//  PRIVATE METHODS  //

void XSIO::Virtual::Worker::m_suspend() {
  $_PP_SCOPE() {
    $_UNUSED $_AUTO = $::Lock::guard(m_mutex);
    m_stopped.compare_exchange_strong(false, true);
  }

  // and attempt waiting whilst possible to do so
  for (auto now = state(); !m_safe(now);) now = m_until(now);
}

void XSIO::Virtual::Worker::m_resume() {
  auto lock = $::Lock::scope(m_mutex);
  m_stopped.compare_exchange_strong(true, false);
  lock.unlock(), m_cv_wake.notify_one();
}

void XSIO::Virtual::Worker::m_checkpoint() {
  // ignore if not currently paused
  if (!m_stopped) return;

  // cache the previous worker state
  auto original = m_update(state(), State::STOPPED);

  // and wait until we can start the world again
  auto lock = $::Lock::scope(m_mutex);
  m_cv_wake.wait(lock, [&] { return !m_stopped; });
  lock.unlock(), m_update(State::STOPPED, original);
}

void XSIO::Virtual::Worker::m_stall() {
  // declare as currently in the idle state
  m_idle.compare_exchange_strong(false, true);
  m_update(State::ACQUIRING, State::SLEEPING);

  auto lock = $::Lock::scope(m_mutex); // prepare the lock to be used now
  const auto duration = m_runtime->options()->worker.wait_time.underlying();
  m_cv_idle.wait_for(lock, duration, [&] { return !m_idle || !m_runtime->running(); });
  m_idle.compare_exchange_strong(true, false), lock.unlock(); // declare not idle now

  // ensure we go back to the acquiring state
  m_update(State::SLEEPING, State::ACQUIRING);
}

bool XSIO::Virtual::Worker::m_safe(State state) const noexcept {
  switch (state) {
  case State::NATIVE: $_FALLTHROUGH;
  case State::STOPPED: $_FALLTHROUGH;
  case State::SLEEPING: $_FALLTHROUGH;
  case State::SHUTDOWN: return true;
  default: return false; // heap-unsafe
  }
}

XSIO::Virtual::State XSIO::Virtual::Worker::m_until(State current) {
  auto lock = $::Lock::scope(m_mutex); // prepare lock
  m_cv_state.wait(lock, [&] { return state() != current; });
  return lock.unlock(), m_state; // and return the state
}

XSIO::Virtual::State XSIO::Virtual::Worker::m_update(State expected, State desired) {
  auto lock = $::Lock::scope(m_mutex); // prepare lock
  m_state.compare_exchange_assert(expected, desired);
  return lock.unlock(), m_cv_state.notify_all(), expected;
}

void XSIO::Virtual::Worker::m_process(Async::Scheduler *scheduler) {
  Switch::Context::yield_to_scheduler(this), scheduler->release(this);
}

void XSIO::Virtual::Worker::m_main() {
  // pre-wait for the context to be ready
  m_runtime->ready();

  // get the scheduler instance as well
  auto *scheduler = m_runtime->scheduler();
  m_update(State::CLEANED, State::ACQUIRING);

  // attempt running the worker indefinitely
  for (; m_runtime->running(); m_stall()) {
    // attempt scheduling and stall if not available
    if (!scheduler->assign(this)) continue;

    m_update(State::ACQUIRING, State::RUNNING);
    m_process(scheduler); // process worker now
    m_update(State::RUNNING, State::ACQUIRING);
  }

  // when complete, declare as shutdown now
  m_update(State::ACQUIRING, State::SHUTDOWN);
}
