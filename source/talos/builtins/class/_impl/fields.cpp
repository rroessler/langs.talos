/// Talos Modules
#include "talos/runtime/isolate.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/builtins.ipp"

//  PRIVATE METHODS  //

Talos::Member::View TALOS_BUILTIN_TRAITS(Object::Class)::m_attributes(const Object::Class& self, Value::Symbol symbol) {
    const auto& statics = self.statics();  // prepare the statics to resolve
    return statics.contains(symbol) ? statics.at(symbol).get() : nullptr;
}
