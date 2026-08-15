#ifndef _TALOS_BUILTINS_EXCEPTION_HPP
#define _TALOS_BUILTINS_EXCEPTION_HPP

/// Talos Includes
#include "talos/builtins/wrapper.hpp"

namespace Talos::Builtins {

/// @brief Tagged Exception Builtin Traits.
template <> struct Wrapper<Object::Exception> : public Blueprint<Object::Exception, "Exception"> {
  //  PUBLIC METHODS  //

  /// @brief Gets the baseline exception type-class.
  static $::Shared::Pointer<Type::Prototype> typeclass();

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
   * @brief Handles looking up value fields.
   * @param self                      Value instance.
   * @param symbol                    Field symbol.
   */
  static Member::View m_attribute(const Object::Exception &self, const Value::Symbol &symbol);
};

} // namespace Talos::Builtins

#endif
