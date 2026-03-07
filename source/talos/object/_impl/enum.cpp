/// Talos Modules
#include "talos/object/enum.hpp"
#include "talos/globals/roots.hpp"

//  PRIVATE METHODS  //

void Talos::Object::Enum::m_yield(const Enum& self, const Globals::Each& yield) {
    for (auto& variant : self.m_attrs()->variants | std::views::values) {
        yield(variant.name), yield(variant.label), yield(variant.value->reference());
    }
}
