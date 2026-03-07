/// Talos Modules
#include "talos/function/jitted.hpp"
#include "talos/globals/roots.hpp"

//  PRIVATE METHODS  //

void Talos::Function::Jitted::m_yield(const Jitted& self, const Globals::Each& yield) {
    auto* attributes = self.m_attrs();
    yield(attributes->context.environment());
}
