/// Forge Modules
#include "forge/runtime/isolate.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/builtins.ipp"

//  PRIVATE METHODS  //

Forge::Member::View FORGE_BUILTIN_TRAITS(Object::Class)::m_attributes(const Object::Class& self, Value::Symbol symbol) {
    const auto& statics = self.statics();  // prepare the statics to resolve
    return statics.contains(symbol) ? statics.at(symbol).get() : nullptr;
}
