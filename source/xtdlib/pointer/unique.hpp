#ifndef _XTDLIB_POINTER_UNIQUE_HPP
#define _XTDLIB_POINTER_UNIQUE_HPP

/// Library Includes
#include "xtdlib/portable/stdlib.hpp"

namespace $::Unique {

/// @brief Unique Pointer Typing.
template <class T, class D = std::default_delete<T>> using Pointer = std::unique_ptr<T, D>;

/// @brief Factory method for creating unique pointers.
template <class T> static inline constexpr Pointer<T> From(T *pointer) { return std::unique_ptr<T>(pointer); }

/// @brief Factory method for creating unique pointers.
template <class T, class... As> static inline constexpr Pointer<T> New(As &&...args) noexcept {
  static_assert(std::constructible_from<T, As...>);
  return std::make_unique<T>(std::forward<As>(args)...);
}

} // namespace $::Unique

#endif
