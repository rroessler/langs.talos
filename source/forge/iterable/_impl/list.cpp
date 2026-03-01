/// Forge Modules
#include "forge/iterable/list.hpp"
#include "forge/globals/roots.hpp"

//  PRIVATE METHODS  //

void Forge::Iterable::List::m_yield(const List& self, const Globals::Each& yield) { yield(self.m_attrs()->values); }
