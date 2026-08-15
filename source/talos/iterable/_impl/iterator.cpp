/// Talos Includes
#include "talos/iterable/iterator.hpp"
#include "talos/globals/roots.hpp"

//  PRIVATE METHODS  //

void Talos::Iterable::Iterator::m_yield(const Iterator &self, Globals::Each &yield) {
  auto *attributes = self.m_wrapper();
  yield(attributes->state);
  yield(attributes->value);
}
