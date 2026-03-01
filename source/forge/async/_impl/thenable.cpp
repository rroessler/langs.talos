/// Forge Modules
#include "forge/async/thenable.hpp"
#include "forge/async/future.hpp"
#include "forge/runtime/isolate.hpp"

//  PUBLIC METHODS  //

Forge::Async::Result Forge::Async::Thenable::await(Thread* thread) noexcept { return Deferred::await(thread); }
Forge::Value::Any Forge::Async::Thenable::await(Runtime::Isolate* isolate) noexcept {
    auto result = await(isolate->thread());
    if (result.has_value()) return result.value();
    else return isolate->panic(result.error());
}

bool Forge::Async::Thenable::resolve(Runtime::Isolate* isolate, Value::Any value) noexcept {
    return Deferred::resolve(isolate->thread(), value);
}

bool Forge::Async::Thenable::reject(Runtime::Isolate* isolate, Value::Any exception) noexcept {
    return Deferred::reject(isolate->thread(), exception);
}
