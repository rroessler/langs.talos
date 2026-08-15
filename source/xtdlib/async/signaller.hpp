#ifndef _XTDLIB_ASYNC_SIGNALLER_HPP
#define _XTDLIB_ASYNC_SIGNALLER_HPP

/// Library Includes
#include "xtdlib/async/atomic.hpp"
#include "xtdlib/chrono/duration.hpp"
#include "xtdlib/mutex/lock.hpp"
#include "xtdlib/mutex/types.hpp"

namespace $::Async {

/// @brief Wait Flag Implementation.
class Signaller {
  //  PROPERTIES  //

  /// @brief Mutex to signal against.
  Mutex::Auto &m_mutex;

  /// @brief An internal condition variable.
  std::condition_variable m_cv;

  /// @brief The current signalling state.
  Atomic<bool> m_state = false;

public:
  //  CONSTRUCTORS  //

  /// @brief Do not allow construction without a mutex.
  constexpr Signaller() = delete;

  /**
   * @brief Constructs an atomic flag.
   * @param mutex                 Mutex to encapsulate.
   */
  constexpr Signaller(Mutex::Auto &mutex) : m_mutex(mutex) {}

  //  PUBLIC METHODS  //

  /// @brief Gets the current flag state.
  inline bool state() const noexcept { return m_state; }

  /// @brief Allows other instances to guard against the internal mutex.
  inline constexpr auto guard() { return Lock::guard(m_mutex); }

  /// @brief Waits for flag to be released.
  inline void wait() {
    auto lock = Lock::scope(m_mutex); // lock the state
    m_cv.wait(lock, [&]() -> bool { return m_state; });
  }

  /**
   * @brief Waits for a flag to be released.
   * @param duration          Duration to wait.
   */
  inline void wait(const Chrono::Duration &duration) {
    auto lock = $::Lock::scope(m_mutex); // prepare the lock now to wait on
    m_cv.wait_for(lock, duration.underlying(), [&] -> bool { return m_state; });
  }

  /// @brief Signals semaphore completion.
  inline bool notify() {
    auto lock = Lock::scope(m_mutex); // lock the state
    bool first = m_state.compare_exchange_strong(false, true);
    return lock.unlock(), m_cv.notify_all(), first;
  }

  /// @brief Resets the signaller state.
  inline bool reset() {
    auto lock = Lock::scope(m_mutex); // lock the state
    bool first = m_state.compare_exchange_strong(true, false);
    return lock.unlock(), m_cv.notify_all(), first;
  }
};

} // namespace $::Async

#endif