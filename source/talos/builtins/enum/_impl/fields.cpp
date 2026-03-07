/// Talos Modules
#include "talos/object/enum.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"

//  PRIVATE METHODS  //

Talos::Member::View TALOS_BUILTIN_TRAITS(Object::Enum)::m_attributes(const Object::Enum& self, Value::Symbol symbol) {
    auto* variant = self.resolve(symbol);  // resolve
    return variant ? variant->value.get() : nullptr;
}
