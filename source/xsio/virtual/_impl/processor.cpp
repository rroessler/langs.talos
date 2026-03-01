/// XSIO Modules
#include "xsio/virtual/processor.hpp"
#include "xsio/async/manager.hpp"

//  CONSTRUCTORS  //

XSIO::Virtual::Processor::Processor(Async::Manager* manager, Async::Scheduler* scheduler) :
    m_manager(manager), m_tasks($::New().unique<Task::Queue>()), m_timers($::New().unique<Timer::Cache>(scheduler)) {}

//  PUBLIC METHODS  //

XSIO::Virtual::Thread* XSIO::Virtual::Processor::acquire() {
    // ensure the manager is actually running firstly
    if (!m_manager->running()) return nullptr;

    // ensure the processor is currently running tasks
    $_ASSERT(m_worker, "Processor not assigned to a worker");

    // get the scheduler instance now
    auto* scheduler = m_manager->scheduler();

    // randomly pull a global task (to mimic avoid locks)
    if (m_rdev.next() % m_manager->options()->vprocs.tasks_priority == 0) {
        if (auto* thread = scheduler->tasks()->acquire()) return thread;
    }

    // attempt acquiring from the local queue
    if (auto* thread = m_tasks->acquire()) return thread;

    // otherwise check against the global scheduler now
    if (auto* thread = scheduler->tasks()->acquire()) return thread;

    // attempt balancing if we reach here instead (could lead to a recursion error??)
    return scheduler->steal(this) ? acquire() : nullptr;
}

void XSIO::Virtual::Processor::schedule(Thread* thread) {
    $_ASSERT(thread->state() == State::READY, "Thread not ready for scheduling");
    if (!m_tasks->schedule(thread)) m_manager->scheduler()->schedule(thread);
}
