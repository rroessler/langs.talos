#ifndef _XSIO_VIRTUAL_PROCESSOR_HPP
#define _XSIO_VIRTUAL_PROCESSOR_HPP

/// XSIO Includes
#include "xsio/task/queue.hpp"
#include "xsio/timer/cache.hpp"
#include "xsio/timer/event.hpp"
#include "xsio/virtual/worker.hpp"

namespace XSIO::Virtual {

/// @brief Virtual Processor (represents virtual processing queue).
class Processor {
  //  PROPERTIES  //

  /// @brief Asynchronous runtime manager.
  Async::Manager *m_runtime;

  /// @brief Currently assigned worker instance.
  $::Async::Atomic<Worker *> m_worker = nullptr;

  /// @brief Random state to be used.
  $::Random::Device::Simple m_rdev = {};

  /// @brief Current task queue.
  $::Unique::Pointer<Task::Queue> m_tasks = nullptr;

  /// @brief Bound timer cache.
  $::Unique::Pointer<Timer::Cache> m_timers = nullptr;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a virtual processor.
   * @param runtime                   Runtime manager.
   * @param scheduler                 Runtime scheduler.
   */
  explicit Processor();
  explicit Processor(Async::Manager *runtime);
  explicit Processor(Async::Manager *runtime, Async::Scheduler *scheduler);

  //  PUBLIC METHODS  //

  /// @brief Gets the worker assignment flag.
  inline constexpr bool running() const noexcept { return m_worker != nullptr; }

  /// @brief Denotes how big the processor queue is.
  inline constexpr size_t pending() const noexcept { return m_tasks->size(); }

  /// @brief Gets the timers cache.
  inline constexpr Timer::Cache *timers() const noexcept { return m_timers.get(); }

  /// @brief Handles acquiring a new thread.
  inline Thread *acquire() { return m_acquire(); }

  /**
   * @brief Schedules a thread for processing.
   * @param thread                    Thread to schedule.
   */
  inline void schedule(Thread *thread) { return m_schedule(thread); }

  /**
   * @brief Handles attaching/detaching a worker instance.
   * @param worker                    Worker to attach.
   */
  inline constexpr void assign(Worker *worker) { worker->m_processor = this, m_worker = worker; }
  inline constexpr void assign(std::nullptr_t) { m_worker.load()->m_processor = nullptr, m_worker = nullptr; }

  /**
   * @brief Balances this processor into a target.
   * @param target                    Target processor.
   * @param total                     Maximum threads to balance.
   */
  inline size_t balance(Processor *target, size_t total = SIZE_MAX) {
    return m_tasks->balance(target->m_tasks.get(), total);
  }

private:
  //  PRIVATE METHODS  //

  /// @brief Handles acquiring a new thread.
  Thread *m_acquire();

  /**
   * @brief Schedules a thread for processing.
   * @param thread                    Thread to schedule.
   */
  void m_schedule(Thread *thread);
};

} // namespace XSIO::Virtual

#endif
