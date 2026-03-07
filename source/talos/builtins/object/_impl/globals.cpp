/// Talos Modules
#include "talos/runtime/isolate.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/builtins.ipp"

//  PRIVATE METHODS  //

Talos::Value::Any TALOS_BUILTIN_TRAITS(Object::Instance)::m_globals(Runtime::Isolate* isolate) {
    return isolate->create<Object::Class>(name(), shape());
}
