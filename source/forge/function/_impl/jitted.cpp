/// Forge Modules
#include "forge/function/jitted.hpp"
#include "forge/globals/roots.hpp"

//  PRIVATE METHODS  //

void Forge::Function::Jitted::m_yield(const Jitted& self, const Globals::Each& yield) {
    auto* attributes = self.m_attrs();
    yield(attributes->context.environment());
}
