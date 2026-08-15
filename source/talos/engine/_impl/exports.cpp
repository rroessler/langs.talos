/// Talos Includes
#include "talos/engine/exports.hpp"
#include "talos/object/instance.hpp"
#include "talos/runtime/isolate.hpp"

//  PRIVATE METHODS  //

Talos::Value::Any Talos::Engine::Exports::m_open(Runtime::Isolate *isolate) {
  return m_scopes.emplace_back(isolate->create<Object::Instance>());
}

Talos::Value::Any Talos::Engine::Exports::m_close() {
  auto value = m_scopes.back();
  return m_scopes.pop_back(), value;
}
