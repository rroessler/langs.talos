/// Forge Modules
#include "forge/object/enum.hpp"
#include "forge/globals/roots.hpp"

//  PRIVATE METHODS  //

void Forge::Object::Enum::m_yield(const Enum& self, const Globals::Each& yield) {
    for (auto& variant : self.m_attrs()->variants | std::views::values) {
        yield(variant.name), yield(variant.label), yield(variant.value->reference());
    }
}
