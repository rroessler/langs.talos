/// Talos Includes
#include "talos/function/jitted.hpp"
#include "talos/globals/roots.hpp"

//  PRIVATE METHODS  //

void Talos::Function::Jitted::m_yield(const Jitted &self, Globals::Each &yield) {
  auto *attributes = self.m_wrapper();
  yield(attributes->receiver);
  yield(attributes->context.environment());
}
