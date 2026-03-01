/// Forge Modules
#include "forge/function/closure.hpp"
#include "forge/globals/roots.hpp"

//  PRIVATE METHODS  //

void Forge::Function::Closure::m_yield(const Closure& self, const Globals::Each& yield) {
    auto* attributes = self.m_attrs();
    yield(attributes->context.environment());
}
