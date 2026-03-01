/// Vendor Modules
#include <boost/context/detail/fcontext.hpp>

/// XSIO Modules
#include "xsio/async/loop.hpp"
#include "xsio/async/manager.hpp"
#include "xsio/context/switch.hpp"
#include "xsio/context/transfer.hpp"
#include "xsio/virtual/worker.hpp"

/// Forward Declarations
$_FWD(Transfer jump(Pointer, void *), XSIO::Context::Operation)
$_FWD(Pointer make(void *, size_t, void (*)(Transfer)), XSIO::Context::Operation)

//  PROPERTIES  //

/// @brief Global thread instance.
thread_local static XSIO::Virtual::Thread *g_thread = nullptr;

//  PUBLIC METHODS  //

XSIO::Context::Transfer XSIO::Context::Operation::jump(const Pointer to, void *vp) {
    auto transfer = boost::context::detail::jump_fcontext(to, vp);
    return { .data = transfer.data, .fctx = transfer.fctx };
}

XSIO::Context::Pointer XSIO::Context::Operation::make(void *sp, size_t size, void (*fn)(Transfer)) {
    // prepare a static delegate for converting our transfer types
    static auto s_delegate = [fn](boost::context::detail::transfer_t transfer) {
        fn({ .data = transfer.data, .fctx = transfer.fctx });  // run callback
    };

    // and construct the result context constructor to the used now
    return boost::context::detail::make_fcontext(sp, size, [](auto transfer) { s_delegate(transfer); });
}

void XSIO::Switch::wait_for_thread(Virtual::Thread *thread, Virtual::Processor *processor) {
    if (thread->m_callback) thread->m_callback(thread, processor), thread->m_callback = nullptr;
}

void XSIO::Switch::wait_for_scheduler(Async::Loop *loop) {
    // get the current worker instance
    auto *thread = loop->thread();
    auto *worker = thread->m_worker;

    // update the current thread state to be waiting now
    static constexpr auto expected = Virtual::State::WORKING;
    static constexpr auto desired = Virtual::State::WAITING;
    thread->m_update(expected, desired), g_thread = nullptr;

    // and attempt jump function contexts
    auto transfer = Context::Operation::jump(worker->context(), nullptr);

    $_ASSERT(transfer.data == thread, "Failed function-context jump");
    $_ASSERT(thread->m_worker == worker, "Worker mismatch after context jump");
    $_ASSERT(worker->thread() == thread, "Scheduler mismatch after context jump");

    // successful, so update as necessary
    worker->context() = transfer.fctx, g_thread = thread;
}

void XSIO::Switch::yield_to_worker(Virtual::Worker *worker) {
    auto *loop = worker->m_scheduler.load();
    loop->awaken();  // ensure woken up

    $_ASSERT(worker->thread() == nullptr, "Worker already assigned");  // failure
    if ((worker->m_thread = loop)->m_stack == nullptr) m_allocate(loop, worker);

    loop->m_worker = worker;  // update the thread worker to be used now
    loop->m_update(Virtual::State::READY, Virtual::State::WORKING);
    loop->m_ts.compare_exchange_strong(Timer::Yield::NEVER, Timer::Point());

    // attempt jumping context now
    auto transfer = Context::Operation::jump(loop->m_context, loop);
    $_ASSERT(transfer.data == nullptr, "Failed function-context jump");

    loop->m_worker = nullptr;
    worker->m_thread = nullptr;
    loop->m_context = transfer.fctx;
    loop->m_ts = Timer::Yield::NEVER;

    $_ASSERT(loop->state() == Virtual::State::WAITING, "Scheduler thread not completed");
    $_ASSERT(worker->m_scheduler == loop, "Scheduler thread mismatch occured");
}

void XSIO::Switch::yield_to_thread(Async::Loop *loop, Virtual::Thread *to) {
    auto *from = loop->thread();  // incoming scheduler loop thread
    $_ASSERT(!to->is<Async::Loop>(), "Expected a non-scheduler thread");

    auto *worker = from->m_worker;  // get the worker instance now
    $_ASSERT(worker->m_scheduler == from, "Scheduler thread mismatch");
    $_ASSERT(worker->thread() == from, "Worker thread mismatch");

    from->m_update(Virtual::State::WORKING, Virtual::State::WAITING);
    from->m_ts = Timer::Yield::NEVER, worker->m_thread = to, from->m_worker = nullptr;

    // ensure the incoming thread has a valid stack
    if (to->m_stack == nullptr) m_allocate(to, worker);

    // set the incoming thread into a valid state for running
    to->m_update(Virtual::State::READY, Virtual::State::WORKING);
    to->m_ts.compare_exchange_strong(Timer::Yield::NEVER, Timer::Point());
    to->m_worker = worker;  // and swap the worker instance back again

    // attempt the context jump now
    auto transfer = Context::Operation::jump(to->m_context, to);
    $_ASSERT(transfer.data == to, "Failed function-context jump");
    to->m_context = transfer.fctx, g_thread = from;  // update now

    // re-enter scheduler thread
    $_ASSERT(worker->m_scheduler == from, "Scheduler thread mismatch");
    $_ASSERT(from->m_worker == worker, "Scheduler worker mismatch");
    $_ASSERT(worker->thread() == from, "Worker thread mismatch");

    // ensure we get the timestamp assigned in milliseconds
    from->m_ts.compare_exchange_strong(Timer::Yield::NEVER, Timer::Point());
}

void XSIO::Switch::yield_to_scheduler(Virtual::Thread *thread, Virtual::State state) {
    yield_to_scheduler(thread, state, nullptr);
}

void XSIO::Switch::yield_to_scheduler(Virtual::Thread *thread, Virtual::State state, Context::Callback &&callback) {
    auto *worker = thread->m_worker;
    auto *loop = worker->m_scheduler.load();

    // run some simple assertions that should always be true
    $_ASSERT(loop->state() == Virtual::State::WAITING, "Scheduler thread not ready");
    $_ASSERT(loop->is<Async::Loop>(), "Expected a scheduler thread");
    $_ASSERT(!thread->is<Async::Loop>(), "Thread should not be a scheduler");
    $_ASSERT(thread->m_callback == nullptr, "Thread should not have a callback");

    // attempt running our necessary details now
    thread->m_update(Virtual::State::WORKING, state);
    thread->m_ts = Timer::Yield::NEVER, thread->m_worker = nullptr;
    thread->m_callback = std::move(callback);  // set the wait-callback

    // update the scheduler details now
    loop->m_update(Virtual::State::WAITING, Virtual::State::WORKING);
    loop->m_worker = worker, worker->m_thread = loop;  // resolve worker

    // attempt the context jump now
    auto transfer = Context::Operation::jump(loop->m_context, thread);
    $_ASSERT(transfer.data == thread, "Failed function-context jump");

    // update our final details now
    loop = thread->m_worker->m_scheduler.load();
    loop->m_context = transfer.fctx, g_thread = thread;
}

//  PRIVATE METHODS  //

void XSIO::Switch::m_allocate(Virtual::Thread *thread, Virtual::Worker *worker) {
    $_ASSERT(thread->m_stack == nullptr, "Thread stack already acquired");
    auto *stack = worker->m_manager->scheduler()->acquire<Memory::Stack>();
    $_ASSERT(stack, "Failed to allocate a thread-stack");  // ensure allocated

    thread->m_stack = stack;  // update the stack value before making a function-context now
    thread->m_context = Context::Operation::make(stack->high(), stack->size(), &Switch::m_transfer);
}

$_NORETURN void XSIO::Switch::m_transfer(Context::Transfer transfer) {
    // cast the incoming transfer data now
    auto *thread = static_cast<Virtual::Thread *>(transfer.data);

    auto *worker = thread->m_worker;          // get the worker instance
    auto *loop = worker->m_scheduler.load();  // get the scheduler instance

    // set the current thread instance
    g_thread = thread;

    // ensure we have a non-thread mismatch now
    $_ASSERT(worker->thread() == thread, "Context handler thread-mismatch");

    // if we have a scheduler thread, then run another assertion
    if (!thread->is<Async::Loop>()) loop->m_context = transfer.fctx;
    else worker->m_context = transfer.fctx, $_ASSERT(loop == thread, "Scheduler thread mismatch");

    // and run the handler now to be used
    thread->m_execute(), thread->exit();
}
