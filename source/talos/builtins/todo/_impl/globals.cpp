/// Talos Modules
#include "talos/function/native.hpp"
#include "talos/runtime/isolate.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"

//  PRIVATE METHODS  //

Talos::Value::Any TALOS_BUILTIN_TRAITS(Builtins::Custom::Todo)::m_panic(
    Runtime::Isolate* isolate, const Function::Arguments& args) {
    // get the baseline argument to be handled now
    auto reason = args.at(0, Value::Void());

    // handle the incoming argument based on its typing now
    if (reason.is<Value::Void>()) return isolate->todo();
    if (reason.is<String::Dynamic>()) return isolate->todo(reason.as<String::Dynamic>());

    // otherwise through a typing error now since invalid
    return isolate->panic(3000301, reason.type_name(), "String?");
}

Talos::Value::Any TALOS_BUILTIN_TRAITS(Builtins::Custom::Todo)::m_globals(Runtime::Isolate* isolate) {
    return isolate->create<Function::Native>(m_panic, name());
}
