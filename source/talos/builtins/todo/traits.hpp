#ifndef _TALOS_BUILTINS_TODO_HPP
#define _TALOS_BUILTINS_TODO_HPP

/// Talos Includes
#include "talos/builtins/wrapper.hpp"

/// Forward Declarations
$_FWD(Talos::Builtins::Custom, struct Todo)

namespace Talos::Builtins {

/// @brief Todo Custom Builtin Traits.
template <> struct Wrapper<Custom::Todo> : public Define<Custom::Todo, "Todo", Adapter::GLOBALS, Adapter::TYPEDEFS> {
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

  /**
   * @brief Handles executing panics for the "Todo" builtin.
   * @param isolate                   Runtime isolate.
   * @param args                      Function arguments.
   */
  static Value::Any m_panic(Isolate *isolate, const Function::Args &args);
};

} // namespace Talos::Builtins

#endif
