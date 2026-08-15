#ifndef _TALOS_BUILTINS_CLASS_HPP
#define _TALOS_BUILTINS_CLASS_HPP

/// Talos Includes
#include "talos/builtins/wrapper.hpp"

namespace Talos::Builtins {

/// @brief Tagged Class Builtin Traits.
template <> struct Wrapper<Object::Class> : public Define<Object::Class, "Class", Adapter::FIELDS> {
protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles instantiating globals.
   * @param isolate                   Runtime isolate.
   * @param prototype                 Prototype instance.
   */
  static Value::Any m_globals(Isolate *isolate, const Object::Class &prototype);

  /**
   * @brief Handles looking up class fields.
   * @param self                      Class object.
   * @param symbol                    Field symbol.
   */
  static Member::View m_attribute(const Object::Class &self, const Value::Symbol &symbol);
};

} // namespace Talos::Builtins

#endif
