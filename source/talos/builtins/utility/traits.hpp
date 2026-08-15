#ifndef _TALOS_BUILTINS_UTILITY_HPP
#define _TALOS_BUILTINS_UTILITY_HPP

/// Talos Includes
#include "talos/builtins/wrapper.hpp"

/// Forward Declarations
$_FWD(Talos::Builtins::Custom, struct Utility)

namespace Talos::Builtins {

/// @brief Utility Custom Builtin Traits.
template <> struct Wrapper<Custom::Utility> : public Define<Custom::Utility, "Utility", Adapter::TYPEDEFS> {
protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles defining global type definitions.
   * @param globals                     Global type-world.
   */
  static void m_typedefs(Type::World *globals);
};

} // namespace Talos::Builtins

#endif
