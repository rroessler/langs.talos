#ifndef _XTDLIB_POINTER_SHARED_HPP
#define _XTDLIB_POINTER_SHARED_HPP

/// Library Includes
#include "xtdlib/portable/stdlib.hpp"

namespace $::Shared {

/// @brief Shared Pointer Typing.
template <class T> using Pointer = std::shared_ptr<T>;

/// @brief Factory method for creating shared pointers.
template <class T, class... As> static inline constexpr Pointer<T> New(As &&...args) noexcept {
  static_assert(std::constructible_from<T, As...>);
  return std::make_shared<T>(std::forward<As>(args)...);
}

/// @brief Allows Internal Conversions.
template <class T> class $_ABSTRACT Recast : public std::enable_shared_from_this<Recast<T>> {
  //  TYPEDEFS  //

  /// @brief Hide all the internally used methods.
  using std::enable_shared_from_this<Recast<T>>::enable_shared_from_this;
  using std::enable_shared_from_this<Recast<T>>::weak_from_this;
  using std::enable_shared_from_this<Recast<T>>::shared_from_this;

protected:
  //  PRIVATE METHODS  //

  /// @brief Allows getting the self value.
  inline constexpr Pointer<T> m_self() const noexcept { return m_as<T>(); }

  /// @brief Handles safely casting to another shared-pointer.
  template <std::derived_from<T> U> inline constexpr Pointer<U> m_as() const noexcept {
    return std::const_pointer_cast<U>(std::static_pointer_cast<const U>(shared_from_this()));
  }
};

} // namespace $::Shared

#endif
