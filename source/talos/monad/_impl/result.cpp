/// Talos Includes
#include "talos/monad/result.hpp"
#include "talos/globals/roots.hpp"
#include "talos/runtime/isolate.hpp"

//  PUBLIC METHODS  //

Talos::Monad::Result Talos::Monad::Success(Runtime::Isolate *isolate, const Value::Any &value) {
  return isolate->create<Result>(value, std::true_type());
}

Talos::Monad::Result Talos::Monad::Failure(Runtime::Isolate *isolate, const Value::Any &value) {
  return isolate->create<Result>(value, std::false_type());
}

//  PRIVATE METHODS  //

void Talos::Monad::Result::m_yield(const Result &self, Globals::Each &yield) { yield(self.m_wrapper()->storage); }
