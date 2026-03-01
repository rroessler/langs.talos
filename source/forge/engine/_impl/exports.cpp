/// Forge Modules
#include "forge/engine/exports.hpp"
#include "forge/object/instance.hpp"
#include "forge/runtime/isolate.hpp"

//  PUBLIC METHODS  //

Forge::Value::Any Forge::Engine::Exports::open(Runtime::Isolate* isolate) {
    return m_scopes.emplace_back(isolate->create<Object::Instance>());
}

Forge::Value::Any Forge::Engine::Exports::close() {
    auto value = m_scopes.back();
    return m_scopes.pop_back(), value;
}
