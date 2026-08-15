#ifndef _XTDLIB_UNIT_STRONG_HPP
#define _XTDLIB_UNIT_STRONG_HPP

/// Library Includes
#include "xtdlib/portable/stdlib.hpp"

namespace $::Unit {

/// @brief Encapsulates strongly-typed numerics.
template <class T, class P> class Strong {
  //  TYPEDEFS  //

  /// @brief Ensure the typing is actually arithmetic.
  static_assert(std::is_arithmetic_v<T>, "Strong units expect a numeric type");

protected:
  //  PROPERTIES  //

  /// @brief The encapsulated value.
  T m_value = m_minimum();

public:
  //  CONSTRUCTORS  //

  /// @brief Allow default construction.
  constexpr Strong() = default;

  /// @brief Allow copy/move constructors/
  constexpr Strong(const T &value) : m_value(value) {}
  constexpr Strong(T &&value) : m_value(std::move(value)) {}

  //  OPERATOR METHODS  //

  inline constexpr operator T &() noexcept { return m_value; }
  inline constexpr operator const T &() const noexcept { return m_value; }

  inline constexpr Strong &operator=(const T &value) { return m_value = value, *this; }
  inline constexpr Strong &operator=(T &&value) { return m_value = std::move(value), *this; }

protected:
  //  PRIVATE METHODS  //

  static inline constexpr T m_minimum() noexcept { return std::numeric_limits<T>::min(); }
  static inline constexpr T m_maximum() noexcept { return std::numeric_limits<T>::max(); }
};

} // namespace $::Unit

#endif
