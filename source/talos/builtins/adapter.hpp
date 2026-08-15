#ifndef _TALOS_BUILTINS_ADAPTER_HPP
#define _TALOS_BUILTINS_ADAPTER_HPP

/// Talos Includes
#include "talos/forward/builtins.hpp"

namespace Talos::Builtins {

/// @brief Associated Adapter Enumeration.
enum class Adapter : uint8_t {
  GLOBALS,   // Global value registration.
  TYPEDEFS,  // Type definition registration.
  PROTOTYPE, // Defines a class-prototype.

  FIELDS,    // Attributes callbacks resolution.
  OPERATORS, // Operator callback resolution.
};

} // namespace Talos::Builtins

#endif
