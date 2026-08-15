/// Talos Includes
#include "talos/function/closure.hpp"
#include "talos/globals/roots.hpp"

//  PRIVATE METHODS  //

void Talos::Function::Closure::m_yield(const Closure &self, Globals::Each &yield) {
  auto *attributes = self.m_wrapper();
  yield(attributes->receiver);
  yield(attributes->context.environment());
}
