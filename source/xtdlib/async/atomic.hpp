#ifndef _XTDLIB_ASYNC_ATOMIC_HPP
#define _XTDLIB_ASYNC_ATOMIC_HPP

/// Library Includes
#include "xtdlib/debug/assert.hpp"

namespace $::Async {

/// @brief Atomic Container Class.
template <class T> struct Atomic : public std::atomic<T> {
  //  CONSTRUCTORS  //

  /// @brief Inherit the base constructors.
  using std::atomic<T>::atomic;

  //  OPERATOR METHODS  //

  /// @brief Allow using the base copy-assignments.
  using std::atomic<T>::operator=;

  //  PUBLIC METHODS  //

  /**
   * @brief Allows comparing against non-references.
   * @param expected              Current expected value.
   * @param desired               Desired exchange value.
   * @param order                 Memory ordering to use.
   */
  inline bool compare_exchange_weak(T expected, T desired, std::memory_order order = std::memory_order_seq_cst) {
    return std::atomic<T>::compare_exchange_weak(expected, desired, order);
  }

  /**
   * @brief Allows comparing against non-references.
   * @param expected              Current expected value.
   * @param desired               Desired exchange value.
   * @param order                 Memory ordering to use.
   */
  inline bool compare_exchange_strong(T expected, T desired, std::memory_order order = std::memory_order_seq_cst) {
    return std::atomic<T>::compare_exchange_strong(expected, desired, order);
  }

  /**
   * @brief Ensures an exchange succeeds.
   * @param expected              Current expected value.
   * @param desired               Desired exchange value.
   * @param order                 Memory ordering to use.
   */
  inline void compare_exchange_assert(T expected, T desired, std::memory_order order = std::memory_order_seq_cst) {
    $_EXPECT(std::atomic<T>::compare_exchange_strong(expected, desired, order));
  }
};

} // namespace $::Async

#endif
