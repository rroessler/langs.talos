/// Forge Modules
#include "forge/iterable/iterator.hpp"
#include "forge/globals/roots.hpp"

//  PRIVATE METHODS  //

void Forge::Iterable::Iterator::m_yield(const Iterator& self, const Globals::Each& yield) {
    auto* attributes = self.m_attrs();
    yield(attributes->state);
    yield(attributes->value);
}
