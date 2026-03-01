/// Forge Modules
#include "forge/function/native.hpp"
#include "forge/runtime/isolate.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/assert.ipp"

//  PRIVATE METHODS  //

Forge::Value::Any FORGE_BUILTIN_TRAITS(Builtins::Custom::Todo)::m_panic(
    Runtime::Isolate* isolate, const Function::Arguments& args) {
    // get the baseline argument to be handled now
    auto reason = args.at(0, Value::Void());

    // handle the incoming argument based on its typing now
    if (reason.is<Value::Void>()) return isolate->panic(6000900, "The following code has not been implemented yet");
    if (reason.is<String::Dynamic>()) return isolate->panic(6000900, reason);  // given a reason why so we show this

    // otherwise through a typing error now since invalid
    return isolate->panic(3000301, reason.type_name(), "String?");
}

Forge::Value::Any FORGE_BUILTIN_TRAITS(Builtins::Custom::Todo)::m_globals(Runtime::Isolate* isolate) {
    return isolate->create<Function::Native>(m_panic, name());
}
