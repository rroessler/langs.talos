#ifndef _XTDLIB_SERDE_REFLECT_IPP
#define _XTDLIB_SERDE_REFLECT_IPP

/// Vendor Includes
#include <glaze/json.hpp>

/// Library Includes
#include "xtdlib/serde/value.hpp"

namespace $::Serde {

//  TYPEDEFS  //

/// @brief Allow exposing internal details.
struct Reflect : public Value {
  //  PROPERTIES  //

  /// @brief Expose the storage member now.
  using Value::m_storage;

  //  CONSTRUCTORS  //

  /// @brief Allow default construction.
  using Value::Value;
};

} // namespace $::Serde

//  SPECIALIZATIONS  //

template <> struct glz::meta<$::Serde::Value> {
  //  TYPEDEFS  //

  /// @brief Underlying meta-typing.
  using T = $::Serde::Value;

  //  PROPERTIES  //

  /// @brief Underlying storage value.
  static constexpr auto value = &$::Serde::Reflect::m_storage;
};

#endif
