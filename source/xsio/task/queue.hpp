#ifndef _XSIO_TASK_QUEUE_HPP
#define _XSIO_TASK_QUEUE_HPP

/// XSIO Includes
#include "xsio/forward/task.hpp"
#include "xsio/forward/virtual.hpp"

namespace XSIO::Task {

/// @brief Tasks Queue.
class Queue {
  //  PROPERTIES  //

  /// @brief Task operations mutex.
  mutable $::Mutex::Auto m_mutex;

  /// @brief Currently bound tasks.
  std::deque<Virtual::Thread *> m_queue;

public:
  //  CONSTRUCTORS  //

  /// @brief Default constuctor.
  explicit Queue() = default;

  //  PUBLIC METHODS  //

  /// @brief Denotes if the queue is empty.
  inline constexpr bool empty() const noexcept { return m_queue.empty(); }

  /// @brief Gets the size of the queue.
  inline constexpr size_t size() const noexcept { return m_queue.size(); }

  /**
   * @brief Schedules a task for the queue.
   * @param thread                    Thread to schedule.
   * @param limit                     Scheduling limit.
   */
  inline bool schedule(Virtual::Thread *thread, size_t limit = SIZE_MAX) {
    $_UNUSED $_AUTO = $::Lock::guard(m_mutex);
    if (m_queue.size() >= limit) return false;
    return m_queue.push_back(thread), true;
  }

  /// @brief Acquires a task from the queue.
  inline Virtual::Thread *acquire() {
    $_UNUSED $_AUTO = $::Lock::guard(m_mutex);
    if (m_queue.empty()) return nullptr;
    auto *thread = m_queue.front();
    return m_queue.pop_front(), thread;
  }

  /**
   * @brief Handles balancing queue items.
   * @param target                    Target queue.
   * @param total                     Total to balance.
   */
  inline size_t balance(Queue *target, size_t total = SIZE_MAX) {
    // ensure we lock both the processors from other tasks
    $_UNUSED $_AUTO = $::Lock::join(m_mutex, target->m_mutex);

    // cache the initial total to be used
    auto initial = total;

    // we want to level out the processors here
    while (!m_queue.empty() && target->m_queue.size() < m_queue.size()) {
      auto *thread = m_queue.front();
      target->m_queue.push_back(thread);
      m_queue.pop_front(), --total;
    }

    // and declare the result
    return initial - total;
  }
};

} // namespace XSIO::Task

#endif
