/// Forge Modules
#include "forge/runtime/isolate.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/builtins.ipp"

//  PRIVATE METHODS  //

Forge::Member::View FORGE_BUILTIN_TRAITS(Object::Instance)::m_attributes(
    const Object::Instance& self, Value::Symbol symbol) {
    const auto& fields = self.fields();  // prepare the fields to resolve
    return fields.contains(symbol) ? fields.at(symbol).get() : nullptr;
}
