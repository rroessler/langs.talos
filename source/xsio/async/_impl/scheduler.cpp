/// XSIO Includes
#include "xsio/async/scheduler.hpp"
#include "xsio/async/manager.hpp"
#include "xsio/async/watchdog.hpp"

//  CONSTRUCTORS  //

XSIO::Async::Scheduler::Scheduler(Manager *runtime) : m_runtime(runtime), m_storage(runtime->storage()) {
  size_t maximum = std::thread::hardware_concurrency();
  auto limit = m_runtime->options()->vprocs.hardware_limit;
  auto vprocs = std::clamp(limit, 0zu, maximum);
  if (vprocs == 0) vprocs = maximum; // resolve

  // setup all the necessary processors and worker threads
  $_UNUSED $_AUTO = $::Lock::guard(m_storage->mutex.processors);
  for (size_t ii = 0; ii < vprocs; ++ii) {
    // prepare the available processors to be bound now
    auto processor = $::Unique::New<Virtual::Processor>(m_runtime, this);
    m_storage->free.processors.emplace(processor.get()); // declare free
    m_storage->instances.processors.emplace_back(std::move(processor));

    // prepare the available workers to be bound now
    auto worker = $::Unique::New<Virtual::Worker>(m_runtime, this);
    m_storage->instances.workers.emplace_back(std::move(worker));
  }
}

//  PRIVATE METHODS  //

bool XSIO::Async::Scheduler::m_assign(Virtual::Worker *worker) {
  $_ASSERT(worker->processor() == nullptr, "Worker already assigned a processor");

  // attempt acquiring a suitable processor now
  auto *processor = acquire<Virtual::Processor>();
  if (processor == nullptr) return false; // failed

  $_ASSERT(!processor->running(), "Processor already assigned");
  return processor->assign(worker), true; // forcibly assign now
}

void XSIO::Async::Scheduler::m_recycle(Memory::Stack *stack) {
  $_UNUSED $_AUTO = $::Lock::guard(m_storage->mutex.stacks);
  m_storage->free.stacks.push(stack); // emplace the stack
}

void XSIO::Async::Scheduler::m_recycle(Virtual::Thread *thread) {
  $_UNUSED $_AUTO = $::Lock::guard(m_storage->mutex.threads);
  recycle(thread->m_clean()), m_storage->free.threads.emplace(thread);
}

void XSIO::Async::Scheduler::m_recycle(Virtual::Processor *processor) {
  $_UNUSED $_AUTO = $::Lock::guard(m_storage->mutex.processors);
  processor->assign(nullptr), m_storage->free.processors.emplace(processor);
}

void XSIO::Async::Scheduler::m_release(Virtual::Worker *worker) {
  // get the underlying processor instance
  auto *processor = worker->processor();

  // if not currently assigned, then we can ignore immediately
  if ($_LIKELY(processor)) m_recycle(processor);
}
