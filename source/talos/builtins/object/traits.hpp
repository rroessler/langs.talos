#ifndef _TALOS_BUILTINS_OBJECT_HPP
#define _TALOS_BUILTINS_OBJECT_HPP

/// Talos Includes
#include "talos/builtins/wrapper.hpp"

namespace Talos::Builtins {

/// @brief Instance Builtin Traits.
template <> struct Wrapper<Object::Instance> : public Blueprint<Object::Instance, "Object"> {
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
   * @param prototype                 Prototype instance.
   */
  static Value::Any m_globals(Isolate *isolate, const Object::Class &prototype);

  /**
   * @brief Handles looking up object fields.
   * @param self                      Object instance.
   * @param symbol                    Field symbol.
   */
  static Member::View m_attribute(const Object::Instance &self, const Value::Symbol &symbol);
};

/// @brief Object Builtin Traits.
template <> struct Wrapper<Object::Any> : public Wrapper<Object::Instance> {};

} // namespace Talos::Builtins

#endif
