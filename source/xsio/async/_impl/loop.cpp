/// XSIO Modules
#include "xsio/async/loop.hpp"
#include "xsio/async/manager.hpp"
#include "xsio/virtual/worker.hpp"

//  PRIVATE METHODS  //

void XSIO::Async::Loop::m_execute() {
    // attempt running whilst possible to do so
    while (m_manager->running()) {
        // get the current worker and processor
        auto* worker = m_thread->worker();
        auto* processor = worker->processor();

        // fire any potential timer events now
        processor->timers()->fire(m_thread, processor);

        // get the next available thread to schedule
        auto* next = processor->acquire();

        // get the next available thread now
        if (next == nullptr) m_busy(processor);
        else m_acquired(next, processor);
    }

    // if we reach here, then we need to exit safely
    Switch::wait_for_scheduler(this), $::System::unreachable();
}

void XSIO::Async::Loop::m_acquired(Virtual::Thread* thread, Virtual::Processor* processor) {
    // get the current scheduler instance
    auto* scheduler = m_manager->scheduler();

    $_ASSERT(thread->worker() == nullptr, "Thread already assigned");
    $_ASSERT(thread->state() == Virtual::State::READY, "Thread not ready");
    Switch::yield_to_thread(this, thread);  // ensure we switch to thread

    // handle all the available thread states
    switch (auto state = thread->state()) {
        case Virtual::State::READY: scheduler->schedule(thread); break;
        case Virtual::State::RECYCLE: scheduler->recycle(thread); break;
        case Virtual::State::WAITING: Switch::wait_for_thread(thread, processor); break;

        case Virtual::State::PAUSED: $_FALLTHROUGH;
        case Virtual::State::CLEANED: $_FALLTHROUGH;
        case Virtual::State::WORKING: $_FALLTHROUGH;
        case Virtual::State::NATIVE: $_ABORT("Unexpected thread state!");

        default: {
            auto exit_code = static_cast<int32_t>(state) - static_cast<int32_t>(Virtual::State::SHUTDOWN);
            $_ASSERT(exit_code > -1, "Invalid shutdown state '{0}'", static_cast<uint8_t>(state));
            scheduler->recycle(thread), m_manager->exit(exit_code);  // force an exit to occur now
        } break;
    }
}

void XSIO::Async::Loop::m_busy(Virtual::Processor* processor) {
    auto now = Timer::Point();
    auto next = processor->timers()->next();

    // handle various results of the next value
    if (next == Timer::Ticks()) return Switch::wait_for_scheduler(this);

    // attempt running a native section now to stall the loop
    if (next > now) m_thread->native([&] { m_manager->shutdown()->wait(next - now); });
}
