#ifndef _XSIO_ASYNC_SCHEDULER_HPP
#define _XSIO_ASYNC_SCHEDULER_HPP

/// XSIO Includes
#include "xsio/async/storage.hpp"
#include "xsio/memory/stack.hpp"

namespace XSIO::Async {

/// @brief Asynchronous Scheduler.
class Scheduler {
  //  PROPERTIES  //

  /// @brief Asynchronous runtime manager.
  Manager *m_runtime;

  /// @brief Scheduler storage to be bound.
  Storage *m_storage;

public:
  //  CONSTRUCTORS  //

  /// @brief Do not allow default construction.
  explicit Scheduler() = delete;

  /**
   * @brief Constructs a scheduler instance.
   * @param runtime                   Asynchronous runtime.
   */
  explicit Scheduler(Manager *runtime);

  //  PUBLIC METHODS  //

  /// @brief Gets the underlying queue of tasks.
  inline constexpr Task::Queue *tasks() const noexcept { return m_storage->tasks.get(); }

  /// @brief Gets all the available threads.
  inline constexpr const auto &threads() const noexcept { return m_storage->instances.threads; }

  /// @brief Gets all the available workers.
  inline constexpr const auto &workers() const noexcept { return m_storage->instances.workers; }

  /// @brief Gets all the available processors.
  inline constexpr const auto &processors() const noexcept { return m_storage->instances.processors; }

  /// @brief Gets the total task-queue size.
  inline constexpr size_t pending() const noexcept {
    auto predicate = [](size_t acc, const auto &processor) { return acc + processor->pending(); };
    return std::ranges::fold_left(processors(), m_storage->tasks->size(), predicate);
  }

  /// @brief Joins all scheduler workers.
  inline void join() {
    for (const auto &worker : workers()) worker->awaken(); // first awaken, then join
    for (const auto &worker : workers()) worker->join(), $_EXPECT(!worker->running());
  }

  /// @brief Pauses execution of all the available workers.
  inline constexpr auto suspend() {
    for (const auto &worker : workers()) worker->suspend();
    return $::Lambda::Defer([&] { resume(); }); // resume
  }

  /// @brief Resumes execution of all workers.
  inline constexpr void resume() {
    for (const auto &worker : workers()) worker->resume();
  }

  /// @brief Handles acquiring various storage items.
  template <class T> inline T *acquire() { return m_storage->acquire; }

  /**
   * @brief Handles recycling thread stacks.
   * @param stack                    Stack to recycle.
   */
  inline void recycle(Memory::Stack *stack) { return m_recycle(stack); }

  /**
   * @brief Handles recycling virtual threads.
   * @param thread                   Thread to recycle.
   */
  inline void recycle(Virtual::Thread *thread) { return m_recycle(thread); }

  /**
   * @brief Handles recycling virtual processors.
   * @param processor                 Processor to recycle.
   */
  inline void recycle(Virtual::Processor *processor) { return m_recycle(processor); }

  /**
   * @brief Handles assigning a processor to a worker.
   * @param worker                    Worker to assign to.
   */
  inline bool assign(Virtual::Worker *worker) { return m_assign(worker); }

  /**
   * @brief Handles releasing a processor from a worker.
   * @param worker                    Worker to release from.
   */
  inline void release(Virtual::Worker *worker) { return m_release(worker); }

  /**
   * @brief Attempts stealing threads from another processor.
   * @param target                    Target to steal from.
   */
  inline bool steal(Virtual::Processor *target) {
    // attempt stealing from other processor now
    for (const auto &processor : processors()) {
      if (processor.get() == target) continue;
      if (processor->balance(target)) return true;
    }

    // failed to balance any processors
    return false;
  }

  /**
   * @brief Handles scheduling a thread for execution.
   * @param thread                    Thread to schedule.
   * @param processor                 Optional processor.
   */
  inline void schedule(Virtual::Thread *thread, Virtual::Processor *processor = nullptr) {
    // ensure the thread is actually ready for running
    $_ASSERT(thread->state() == Virtual::State::READY);

    // if we can push onto a processor, then do so
    if (processor) return processor->schedule(thread);

    // attempt pushing the thread onto the global task-queue
    m_storage->tasks->schedule(thread), m_awaken();
  }

  /**
   * @brief Handles scheduling an executor.
   * @param args                      Arguments to bind.
   */
  template <std::derived_from<Task::Executor> T, class... As> inline T *schedule(As &&...args) {
    return schedule<T>(static_cast<Virtual::Processor *>(nullptr), std::forward<As>(args)...);
  }

  /**
   * @brief Handles scheduling an executor.
   * @param processor                 Processor to bind.
   * @param args                      Arguments to bind.
   */
  template <std::derived_from<Task::Executor> T, class... As>
  inline T *schedule(Virtual::Processor *processor, As &&...args) {
    auto *thread = acquire<Virtual::Thread>(); // force acquire
    auto *task = thread->assign<T>(std::forward<As>(args)...);
    return thread->awaken(), schedule(thread, processor), task;
  }

private:
  //  PRIVATE METHODS  //

  /** Attempts trying to awaken a worker instance. */
  inline void m_awaken() {
    for (const auto &worker : workers()) {
      if (worker->state() != Virtual::State::SLEEPING) continue;
      if (worker->awaken()) return; // successfully awoke worker
    }
  }

  /**
   * @brief Handles recycling virtual values.
   * @param value                     Item to recycle.
   */
  void m_recycle(Memory::Stack *stack);
  void m_recycle(Virtual::Thread *thread);
  void m_recycle(Virtual::Processor *processor);

  /**
   * @brief Handles assigning a processor to a worker.
   * @param worker                    Worker to assign to.
   */
  bool m_assign(Virtual::Worker *worker);

  /**
   * @brief Handles releasing a processor from a worker.
   * @param worker                    Worker to release from.
   */
  void m_release(Virtual::Worker *worker);
};

} // namespace XSIO::Async

#endif
