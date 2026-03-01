/// XSIO Modules
#include "xsio/async/scheduler.hpp"
#include "xsio/async/loop.hpp"
#include "xsio/async/manager.hpp"
#include "xsio/async/watchdog.hpp"

//  CONSTRUCTORS  //

XSIO::Async::Scheduler::Scheduler(Manager* manager) : m_manager(manager), m_storage($::New().unique<Storage>()) {
    auto maximum = $::Thread::Limits::hardware();
    auto limit = m_manager->options()->vprocs.hardware_limit;
    auto vprocs = std::clamp(limit, 0zu, maximum);
    if (vprocs == 0) vprocs = maximum;  // resolve

    // setup all the necessary processors and worker threads
    $_UNUSED $_AUTO = $::Lock::guard(m_storage->mutex.processors);
    for (size_t ii = 0; ii < vprocs; ++ii) {
        auto processor = $::New().unique<Virtual::Processor>(m_manager, this);
        m_storage->free.processors.emplace(processor.get());  // declare free
        m_storage->instances.processors.emplace_back(std::move(processor));

        auto* thread = acquire<Virtual::Thread>();     // acquire a new thread
        auto* loop = thread->assign<Loop>(m_manager);  // assign scheduler loop
        auto worker = $::New().unique<Virtual::Worker>(m_manager, loop);
        m_storage->instances.workers.emplace_back(std::move(worker));
    }
}

//  PUBLIC METHODS  //

template <>
XSIO::Memory::Stack* XSIO::Async::Scheduler::acquire() {
    $_UNUSED $_AUTO = $::Lock::guard(m_storage->mutex.stacks);
    auto& free = m_storage->free.stacks;  // get the free instances

    // resolve when there are free stacks
    if (free.size()) {
        auto* stack = free.top();
        return free.pop(), stack;
    }

    auto options = m_manager->options()->thread;  // construct the next thread stack
    auto stack = $::New().unique<Memory::Stack>(options.stack_size, options.stack_limit);
    return m_storage->instances.stacks.emplace_back(std::move(stack)).get();
}

template <>
void XSIO::Async::Scheduler::recycle(Memory::Stack* stack) {
    $_UNUSED $_AUTO = $::Lock::guard(m_storage->mutex.stacks);
    m_storage->free.stacks.push(stack);  // emplace the stack
}

template <>
XSIO::Virtual::Thread* XSIO::Async::Scheduler::acquire() {
    $_UNUSED $_AUTO = $::Lock::guard(m_storage->mutex.threads);
    auto& free = m_storage->free.threads;  // get the free instances

    // if we have available threads, then recycle
    if (free.size()) {
        auto* thread = free.top();
        return free.pop(), thread;
    }

    auto thread = $::New().unique<Virtual::Thread>();  // otherwise rebuild
    return m_storage->instances.threads.emplace_back(std::move(thread)).get();
}

template <>
void XSIO::Async::Scheduler::recycle(Virtual::Thread* thread) {
    $_UNUSED $_AUTO = $::Lock::guard(m_storage->mutex.threads);
    recycle(thread->m_clean()), m_storage->free.threads.emplace(thread);
}

template <>
XSIO::Virtual::Processor* XSIO::Async::Scheduler::acquire() {
    // prepare the processors mutex now
    $_UNUSED $_AUTO = $::Lock::guard(m_storage->mutex.processors);

    // get the free instances firstly
    auto& free = m_storage->free.processors;
    if (free.empty()) return nullptr;

    // otherwise we need to pop the top-most free processor
    auto* processor = free.top();
    return free.pop(), processor;
}

template <>
void XSIO::Async::Scheduler::recycle(Virtual::Processor* processor) {
    $_UNUSED $_AUTO = $::Lock::guard(m_storage->mutex.processors);
    processor->assign(nullptr), m_storage->free.processors.emplace(processor);
}

bool XSIO::Async::Scheduler::assign(Virtual::Worker* worker) {
    $_ASSERT(worker->processor() == nullptr, "Worker already assigned a processor");

    // attempt acquiring a suitable processor now
    auto* processor = acquire<Virtual::Processor>();
    if (processor == nullptr) return false;  // failed

    $_ASSERT(!processor->running(), "Processor already assigned");
    return processor->assign(worker), true;  // forcibly assign now
}

void XSIO::Async::Scheduler::release(Virtual::Worker* worker) {
    // get the underlying processor instance
    auto* processor = worker->processor();

    // if not currently assigned, then we can ignore immediately
    if ($_UNLIKELY(processor == nullptr)) return;

    // otherwise remove the processor instance now
    recycle<Virtual::Processor>(processor);
}
