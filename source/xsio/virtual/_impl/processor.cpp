/// XSIO Includes
#include "xsio/virtual/processor.hpp"
#include "xsio/async/manager.hpp"

//  CONSTRUCTORS  //

XSIO::Virtual::Processor::Processor() : Processor($::Global::get<Async::Manager>()) {}
XSIO::Virtual::Processor::Processor(Async::Manager *runtime) : Processor(runtime, runtime->scheduler()) {}
XSIO::Virtual::Processor::Processor(Async::Manager *runtime, Async::Scheduler *scheduler) :
    m_runtime(runtime), m_tasks($::Unique::New<Task::Queue>()), m_timers($::Unique::New<Timer::Cache>(scheduler)) {}

//  PRIVATE METHODS  //

XSIO::Virtual::Thread *XSIO::Virtual::Processor::m_acquire() {
  // ensure the manager is actually running firstly
  if (!m_runtime->running()) return nullptr;

  // ensure the processor is currently running tasks
  $_ASSERT(m_worker, "Processor not assigned to a worker");

  // get the scheduler instance now
  auto *scheduler = m_runtime->scheduler();

  // randomly pull a global task (to attempt avoiding pinned threads)
  if (m_rdev.next() % m_runtime->options()->vprocs.tasks_priority == 0) {
    if (auto *thread = scheduler->tasks()->acquire()) return thread;
  }

  // attempt acquiring from the local queue
  if (auto *thread = m_tasks->acquire()) return thread;

  // otherwise check against the global scheduler now
  if (auto *thread = scheduler->tasks()->acquire()) return thread;

  // attempt balancing if we reach here instead (could lead to a recursion error??)
  return scheduler->steal(this) ? acquire() : nullptr;
}

void XSIO::Virtual::Processor::m_schedule(Thread *thread) {
  $_ASSERT(thread->state() == State::READY, "Thread not ready for scheduling");
  if (!m_tasks->schedule(thread)) m_runtime->scheduler()->schedule(thread);
}
