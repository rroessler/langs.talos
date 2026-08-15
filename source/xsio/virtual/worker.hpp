#ifndef _XSIO_VIRTUAL_WORKER_HPP
#define _XSIO_VIRTUAL_WORKER_HPP

/// XSIO Includes
#include "xsio/switch/transfer.hpp"
#include "xsio/task/scheduler.hpp"
#include "xsio/virtual/state.hpp"

namespace XSIO::Virtual {

/// @brief Virtual Worker (represents an actual OS thread).
class Worker {
  //  TYPEDEFS  //

  /// @brief Allow processors internal access.
  friend class Processor;

  /// @brief Allow context switching internal access.
  friend struct Switch::Context;

  //  PROPERTIES  //

  $::Async::Atomic<bool> m_idle = false;    // Currently idle flag.
  $::Async::Atomic<bool> m_stopped = false; // World paused flag.

  /// @brief The current worker state.
  $::Async::Atomic<State> m_state = State::CLEANED;

  $::Async::Atomic<Thread *> m_thread = nullptr;       // Assigned thread value.
  $::Async::Atomic<Thread *> m_scheduler = nullptr;    // Scheduler loop thread.
  $::Async::Atomic<Processor *> m_processor = nullptr; // Target processor value.

  /// @brief Worker operations mutex.
  mutable $::Mutex::Auto m_mutex;

  /// @brief Asynchronous runtime manager.
  Async::Manager *m_runtime;

  /// @brief Encapsulated thread instance.
  std::thread m_handle;

  /// @brief Bound function-context pointer.
  Switch::Pointer m_context = nullptr;

  std::condition_variable m_cv_idle;  // Idle condition.
  std::condition_variable m_cv_wake;  // Wake condition.
  std::condition_variable m_cv_state; // State condition.

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a virtual worker.
   * @param runtime               Runtime manager.
   * @param scheduler             Scheduler thread.
   */
  explicit Worker();
  explicit Worker(Async::Manager *runtime);
  explicit Worker(Async::Manager *runtime, Async::Scheduler *scheduler);
  explicit Worker(Async::Manager *runtime, Task::Scheduler *scheduler);

  //  PUBLIC METHODS  //

  /// @brief Denotes if the worker is running.
  inline constexpr bool running() const noexcept { return m_state != State::SHUTDOWN; }

  /// @brief Gets the current worker state.
  inline constexpr State state() const noexcept { return m_state; }

  /// @brief Gets the currently assigned thread reference.
  inline constexpr Thread *thread() const noexcept { return m_thread; }

  /// @brief Gets the currently assigned processor reference.
  inline constexpr Processor *processor() const noexcept { return m_processor; }

  /// @brief Gets the current pointer for switching contexts.
  inline constexpr const Switch::Pointer &context() const noexcept { return m_context; }

  /// @brief Pauses the worker from execution.
  inline void suspend() { return m_suspend(); }

  /// @brief Resumes execution of a worker.
  inline void resume() { return m_resume(); }

  /// @brief Forces the worker into a checkpoint state.
  inline void checkpoint() { return m_checkpoint(); }

  /// @brief Attempts joining the worker thread.
  inline void join() {
    for (State now = m_state; now != State::SHUTDOWN; now = m_until(now));
    m_handle.join(); // can now suitably exit the worker and join
  }

  /// @brief Attempts waking the worker.
  inline bool awaken() {
    auto lock = $::Lock::scope(m_mutex); // lock the mutex
    bool first = m_idle.compare_exchange_strong(true, false);
    return lock.unlock(), m_cv_idle.notify_one(), first;
  }

  /**
   * @brief Handles running native-callbacks.
   * @param callback                  Native callback.
   */
  inline void native(Native &&callback) {
    m_update(State::RUNNING, State::NATIVE);
    callback(); // run the native callback
    m_update(State::NATIVE, State::RUNNING);
  }

private:
  //  PRIVATE METHODS  //

  /// @brief Internal worker loop.
  void m_main();

  /// @brief Stalls the worker until needed.
  void m_stall();

  /// @brief Pauses the worker from execution.
  void m_suspend();

  /// @brief Resumes execution of a worker.
  void m_resume();

  /// @brief Forces the worker into a checkpoint state.
  void m_checkpoint();

  /**
   * @brief Handles processing the current work.
   * @param scheduler         Scheduler instance.
   */
  void m_process(Async::Scheduler *scheduler);

  /**
   * @brief Checks for safe states.
   * @param state             State to compare.
   */
  bool m_safe(State state) const noexcept;

  /**
   * @brief Waits until the current state changes.
   * @param current               State to compare against.
   */
  State m_until(State current);

  /**
   * @brief Updates the current worker state.
   * @param expected              Expected state.
   * @param desired               Desired state.
   */
  State m_update(State expected, State desired);
};

} // namespace XSIO::Virtual

#endif
