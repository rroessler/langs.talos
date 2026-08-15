/// Talos Includes
#include "talos/iterable/list.hpp"
#include "talos/globals/roots.hpp"

//  PRIVATE METHODS  //

void Talos::Iterable::List::m_yield(const List &self, Globals::Each &yield) { yield(self.m_wrapper()->values); }
