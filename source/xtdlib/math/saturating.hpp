#ifndef _XTDLIB_MATH_SATURATING_HPP
#define _XTDLIB_MATH_SATURATING_HPP

/// Library Includes
#include "xtdlib/portable/stdlib.hpp"

namespace Math::Saturating {

// #ifndef __cpp_lib_saturation_arithmetic
template <std::integral T> static inline constexpr T add(T x, T y) {
  if (T res; !__builtin_add_overflow(x, y, std::addressof(res))) return res;
  if constexpr (std::unsigned_integral<T>) return std::numeric_limits<T>::max();
  else return x > 0 ? std::numeric_limits<T>::max() : std::numeric_limits<T>::min();
}

template <std::integral T> static inline constexpr T sub(T x, T y) {
  if (T res; !__builtin_sub_overflow(x, y, std::addressof(res))) return res;
  if constexpr (std::unsigned_integral<T>) return std::numeric_limits<T>::min();
  else return x >= 0 ? std::numeric_limits<T>::max() : std::numeric_limits<T>::min();
}

template <std::integral T> static inline constexpr T mul(T x, T y) {
  if (T res; !__builtin_mul_overflow(x, y, std::addressof(res))) return res;
  if constexpr (std::unsigned_integral<T>) return std::numeric_limits<T>::max();
  else if (x > 0 && y > 0) return std::numeric_limits<T>::max(); // overflow occured
  else return x < 0 && y < 0 ? std::numeric_limits<T>::max() : std::numeric_limits<T>::min();
}

template <std::integral T> static inline constexpr T div(T x, T y) {
  if constexpr (std::unsigned_integral<T>) return x / y;
  else if (x != std::numeric_limits<T>::min() || y != T(-1)) return x / y;
  else return std::numeric_limits<T>::max(); // division overflow occured
}
// #endif

} // namespace Math::Saturating

#endif
