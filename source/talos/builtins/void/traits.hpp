#ifndef _TALOS_BUILTINS_VOID_HPP
#define _TALOS_BUILTINS_VOID_HPP

/// Talos Includes
#include "talos/builtins/wrapper.hpp"

namespace Talos::Builtins {

/// @brief Void Builtin Traits.
template <> struct Wrapper<Value::Void> : public Define<Value::Void, "Void", Adapter::GLOBALS, Adapter::TYPEDEFS> {
protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles defining global type definitions.
   * @param globals                     Global type-world.
   */
  static void m_typedefs(Type::World *globals);

  /**
   * @brief Handles instantiating globals.
   * @param isolate                   Runtime isolate.
   */
  static Value::Any m_globals(Isolate *isolate);
};

} // namespace Talos::Builtins

#endif
