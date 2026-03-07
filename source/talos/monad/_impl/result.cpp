/// Talos Modules
#include "talos/monad/result.hpp"
#include "talos/runtime/isolate.hpp"

//  PUBLIC METHODS  //

Talos::Monad::Result Talos::Monad::Success(Runtime::Isolate* isolate, Value::Any value) {
    return isolate->create<Result>(value, std::true_type());
}

Talos::Monad::Result Talos::Monad::Failure(Runtime::Isolate* isolate, Value::Any value) {
    return isolate->create<Result>(value, std::false_type());
}

//  PRIVATE METHODS  //

void Talos::Monad::Result::m_yield(const Result& self, const Globals::Each& yield) {
    auto* attributes = self.m_attrs();
    yield(attributes->storage);
}
