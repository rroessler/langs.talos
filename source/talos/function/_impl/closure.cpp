/// Talos Modules
#include "talos/function/closure.hpp"
#include "talos/globals/roots.hpp"

//  PRIVATE METHODS  //

void Talos::Function::Closure::m_yield(const Closure& self, const Globals::Each& yield) {
    auto* attributes = self.m_attrs();
    yield(attributes->context.environment());
}
