/// Forge Modules
#include "forge/object/enum.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/assert.ipp"

//  PRIVATE METHODS  //

Forge::Member::View FORGE_BUILTIN_TRAITS(Object::Enum)::m_attributes(const Object::Enum& self, Value::Symbol symbol) {
    auto* variant = self.resolve(symbol);  // resolve
    return variant ? variant->value.get() : nullptr;
}
