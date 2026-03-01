/// Forge Modules
#include "forge/runtime/isolate.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/builtins.ipp"

//  PRIVATE METHODS  //

Forge::Value::Any FORGE_BUILTIN_TRAITS(Object::Instance)::m_globals(Runtime::Isolate* isolate) {
    return isolate->create<Object::Class>(name(), shape());
}
