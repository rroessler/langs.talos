/// Talos Includes
#include "talos/object/enum.hpp"
#include "talos/globals/roots.hpp"

//  PRIVATE METHODS  //

void Talos::Object::Enum::m_yield(const Enum &self, Globals::Each &yield) {
  for (auto &variant : self.m_wrapper()->variants | std::views::values) {
    yield(variant.name), yield(variant.label), yield(variant.value->reference());
  }
}
