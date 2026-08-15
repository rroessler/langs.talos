#ifndef _XTDLIB_LAMBDA_DEFER_HPP
#define _XTDLIB_LAMBDA_DEFER_HPP

/// Library Includes
#include "xtdlib/portable/stdlib.hpp"

namespace $::Lambda {

/// @brief Deferrence Function.
template <class F> class Defer {
  //  PROPERTIES  //

  /// @brief Denotes if the cleanup is pending.
  bool m_pending = true;

  /// @brief Underlying cleanup function.
  F m_cleanup;

public:
  //  CONSTRUCTORS  //

  /// @brief Do not allow copying/moving.
  constexpr Defer(Defer &&) = delete;
  constexpr Defer(const Defer &) = delete;

  /**
   * @brief Constructs a suitable deference handler.
   * @param cleanup                   Cleanup function.
   */
  template <class T> constexpr Defer(T &&cleanup) : m_cleanup(std::forward<T>(cleanup)) {}

  /// @brief Handles cleaning up a deferred function.
  constexpr ~Defer() { dispose(); }

  //  OPERATOR METHODS  //

  inline constexpr Defer &operator=(Defer &&) = delete;
  inline constexpr Defer &operator=(const Defer &) = delete;

  //  PUBLIC METHODS  //

  /// @brief Handles executing the cleanup handler.
  inline constexpr void dispose() {
    if (m_pending) m_cleanup();
    m_pending = false; // clear
  }
};

//  SPECIALIZATIONS  //

template <class T> Defer(T &&) -> Defer<T>;

} // namespace $::Lambda

#endif
