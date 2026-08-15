#ifndef _XTDLIB_UTILITY_PROPERTY_HPP
#define _XTDLIB_UTILITY_PROPERTY_HPP

/// Library Includes
#include "xtdlib/portable/stdlib.hpp"

namespace $::Property {

/// @brief Encapsulates Property Accessors.
template <class T, auto G, auto S> class Accessor {
  //  PROPERTIES  //

  /// @brief Bound value instance.
  T *m_self;

public:
  //  CONSTRUCTORS  //

  /// @brief Ensure we delete all other constructors.
  constexpr Accessor(...) = delete;

  /**
   * @brief Only allow construction with reference.
   * @param self                    Value instance.
   */
  constexpr Accessor(T *self) : m_self(self) {}

  //  OPERATOR METHODS  //

  /// @brief Conversion operator to underlying typing.
  inline constexpr operator auto() const noexcept { return G(m_self); }

  /// @brief Assignment operator for the internal value.
  template <class U> inline constexpr Accessor &operator=(const U &value) { return S(m_self, value), *this; }
};

} // namespace $::Property

#endif
