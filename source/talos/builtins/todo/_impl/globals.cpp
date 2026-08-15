/// Talos Includes
#include "talos/function/native.hpp"
#include "talos/runtime/isolate.hpp"

/// Builtin Includes
#include "talos/builtins/_inline/builtins.ipp"

//  PRIVATE METHODS  //

Talos::Value::Any Talos::Builtins::Wrapper<Talos::Builtins::Custom::Todo>::m_globals(Isolate *isolate) {
  return isolate->create<Function::Native>(m_panic, name());
}

Talos::Value::Any Talos::Builtins::Wrapper<Talos::Builtins::Custom::Todo>::m_panic(Isolate *isolate, const Args &args) {
  // get the baseline argument to be handled now
  auto reason = args.at(0, Value::Void());

  // handle the incoming argument based on its typing now
  if (reason.is<Value::Void>()) return isolate->todo();
  if (reason.is<String::Any>()) return isolate->todo(reason.as<String::Any>());

  // otherwise throw a typing error now since invalid
  return isolate->panic(3000301, reason.brand(), "String?");
}
