/// Talos Modules
#include "talos/object/instance.hpp"
#include "talos/globals/service.hpp"
#include "talos/runtime/isolate.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/builtins.ipp"

//  CONSTRUCTORS  //

Talos::Object::Attributes<Talos::Object::Instance>::Attributes(Runtime::Isolate* isolate) {
    prototype = isolate->service<Globals::Service>()->prototype<Object::Instance>(isolate);
}

//  PRIVATE METHODS  //

void Talos::Object::Instance::m_yield(const Instance& self, const Globals::Each& yield) {
    // emplace the baseline details
    auto* attributes = self.m_attrs();

    // yield the prototype instance now
    yield(attributes->prototype);

    // yield all the underlying member references as necessary now
    for (const auto& member : attributes->fields | std::views::values) yield(member->reference());
}
