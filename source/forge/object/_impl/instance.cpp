/// Forge Modules
#include "forge/object/instance.hpp"
#include "forge/globals/service.hpp"
#include "forge/runtime/isolate.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/builtins.ipp"

//  CONSTRUCTORS  //

Forge::Object::Attributes<Forge::Object::Instance>::Attributes(Runtime::Isolate* isolate) {
    prototype = isolate->service<Globals::Service>()->prototype<Object::Instance>(isolate);
}

//  PRIVATE METHODS  //

void Forge::Object::Instance::m_yield(const Instance& self, const Globals::Each& yield) {
    // emplace the baseline details
    auto* attributes = self.m_attrs();

    // yield the prototype instance now
    yield(attributes->prototype);

    // yield all the underlying member references as necessary now
    for (const auto& member : attributes->fields | std::views::values) yield(member->reference());
}
