#ifndef _XTDLIB_MUTEX_LIGHT_HPP
#define _XTDLIB_MUTEX_LIGHT_HPP

/// Library Includes
#include "xtdlib/async/atomic.hpp"

namespace $::Mutex {

/// @brief 1-Byte Lock Implementation.
class Light {
  //  TYPEDEFS  //

  /// @brief Available Lock States.
  struct State {
    static constexpr uint8_t FREE = 0;
    static constexpr uint8_t LOCKED = 1;
    static constexpr uint8_t PARKED = 2;
  };

  //  PROPERTIES  //

  /// @brief Current state value.
  Async::Atomic<uint8_t> m_state = State::FREE;

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs a light mutex.
  explicit constexpr Light() = default;

  /**
   * @brief Constructs the mutex.
   * @param value             Value to assign.
   */
  constexpr Light(uint8_t value) : m_state(value) {}

  //  OPERATOR METHODS  //

  /// @brief Allows setting the lock value.
  inline Light &operator=(uint8_t value) { return m_state = value, *this; }

  //  PUBLIC METHODS  //

  /// @brief Denotes if the mutex is locked.
  inline bool state() const { return m_state != State::FREE; }

  /// @brief Handles locking our mutex.
  inline void lock() {
    if (m_state.exchange(State::LOCKED, std::memory_order_acquire) == State::FREE) return;
    while (m_state.exchange(State::PARKED, std::memory_order_acquire) != State::FREE) {
      m_state.wait(State::PARKED, std::memory_order_relaxed); // continue parking
    }
  }

  /// @brief Handles unlocking the mutex.
  inline void unlock() {
    if (m_state.exchange(State::FREE, std::memory_order_release) == State::PARKED) m_state.notify_one();
  }
};

} // namespace $::Mutex

#endif
