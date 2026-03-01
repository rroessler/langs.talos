/// Forge Modules
#include "forge/monad/result.hpp"
#include "forge/runtime/isolate.hpp"

//  PUBLIC METHODS  //

Forge::Monad::Result Forge::Monad::Success(Runtime::Isolate* isolate, Value::Any value) {
    return isolate->create<Result>(value, std::true_type());
}

Forge::Monad::Result Forge::Monad::Failure(Runtime::Isolate* isolate, Value::Any value) {
    return isolate->create<Result>(value, std::false_type());
}

//  PRIVATE METHODS  //

void Forge::Monad::Result::m_yield(const Result& self, const Globals::Each& yield) {
    auto* attributes = self.m_attrs();
    yield(attributes->storage);
}
