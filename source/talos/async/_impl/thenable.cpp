/// Talos Includes
#include "talos/async/thenable.hpp"
#include "talos/async/future.hpp"
#include "talos/runtime/isolate.hpp"

//  PUBLIC METHODS  //

Talos::Async::Result Talos::Async::Thenable::await(Thread *thread) noexcept { return Deferred::await(thread); }
Talos::Value::Any Talos::Async::Thenable::await(Runtime::Isolate *isolate) noexcept {
  auto result = await(isolate->thread());
  if (result.has_value()) return result.value();
  else return isolate->panic(result.error());
}

bool Talos::Async::Thenable::resolve(Runtime::Isolate *isolate, const Value::Any &value) noexcept {
  return Deferred::resolve(isolate->thread(), value);
}

bool Talos::Async::Thenable::reject(Runtime::Isolate *isolate, const Value::Any &exception) noexcept {
  return Deferred::reject(isolate->thread(), exception);
}
