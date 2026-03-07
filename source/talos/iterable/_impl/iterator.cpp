/// Talos Modules
#include "talos/iterable/iterator.hpp"
#include "talos/globals/roots.hpp"

//  PRIVATE METHODS  //

void Talos::Iterable::Iterator::m_yield(const Iterator& self, const Globals::Each& yield) {
    auto* attributes = self.m_attrs();
    yield(attributes->state);
    yield(attributes->value);
}
