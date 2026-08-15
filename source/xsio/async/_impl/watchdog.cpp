/// XSIO Includes
#include "xsio/async/watchdog.hpp"
#include "xsio/async/manager.hpp"
#include "xsio/task/scheduler.hpp"

//  CONSTRUCTORS  //

XSIO::Async::Watchdog::Watchdog() : Watchdog($::Global::get<Manager>()) {}
XSIO::Async::Watchdog::Watchdog(Manager *runtime) : m_runtime(runtime), m_thread(&Watchdog::m_main, this) {}

XSIO::Async::Watchdog::~Watchdog() { $_ASSERT(!m_thread.joinable(), "Watchdog not joined before destruction"); }

//  PUBLIC METHODS  //

//! We should be able to safely call "detach" on watchdog threads when we
//! know that the asynchronous context has "stopped". This bypasses the small
//! interval delay for watchdogs and allows us to quick exit. This squeezes
//! approximately 10-20ms off the total runtime for small/fast programs.

void XSIO::Async::Watchdog::join() {
  $_EXPECT(!m_runtime->running(), "Cannot detach watchdog when XSIO context is running");
  m_runtime->options()->watchdog.unsafe_detach ? m_thread.detach() : m_thread.join();
}

//  PRIVATE METHODS  //

void XSIO::Async::Watchdog::m_main() {
  // pre-wait for the context to be ready
  m_runtime->ready();

  // get the scheduler to be used
  auto *scheduler = m_runtime->scheduler();

  // get the applications time-slice and watch-dog interval
  const auto *options = m_runtime->options();
  const auto time_slice = options->thread.time_slice;
  const auto interval = options->watchdog.wakeup_interval;

  // run whilst the runtime is not stopping
  while (m_runtime->running()) {
    // update the current clock details
    m_clock = Timer::Point();

    // and allow yielding all the worker threads
    for (const auto &worker : scheduler->workers()) {
      // ignore if the worker is not actually running
      if (worker->state() != Virtual::State::RUNNING) continue;

      // get the current thread instance to be checked
      auto *thread = worker->thread();
      if (thread == nullptr) continue;

      // ensure the thread is in a valid state
      if (thread->state() == Virtual::State::CLEANED || thread->is<Task::Scheduler>()) continue;

      auto previous = thread->m_ts.load(); // get the old timestamp and validate
      if (previous < Timer::Yield::VALID || previous >= m_clock.load()) continue;

      // determine if we exceeded the maximum time slice
      bool exceeded = (m_clock.load() - previous) > time_slice;

      // and force the thread to yield to the scheduler if it exceeded
      if (exceeded) thread->m_ts.compare_exchange_strong(previous, Timer::Yield::SHOULD);
    }

    // wait a little interval or exit when the manager does
    m_runtime->shutdown()->wait(interval);
  }
}
