/// Talos Modules
#include "talos/module/dynamic.hpp"
#include "talos/crate/service.hpp"
#include "talos/runtime/isolate.hpp"
#include "talos/type/builder.hpp"

/// Metadata Modules
#include "talos/engine/metadata.hpp"
#include "talos/type/metadata.hpp"

//  PRIVATE METHODS  //

void Talos::Module::Dynamic::m_parse(XI::Container*, Metadata::Attributes<Phase::PARSED>*) {}
void Talos::Module::Dynamic::m_analyze(XI::Container*, Metadata::Attributes<Phase::TYPED>* types) {
    types->context() = $::New().unique<Type::Context>(Type::Builder::object());  // prepare now
}

void Talos::Module::Dynamic::m_compile(XI::Container*, Metadata::Attributes<Phase::COMPILED>*) {}

Talos::Async::Thenable* Talos::Module::Dynamic::m_interpret(
    Runtime::Isolate* isolate, Metadata::Attributes<Phase::EXPORTED>* exports) {
    auto* thenable = exports->deferred();  // prepare
    auto* crates = isolate->service<Crate::Service>();

    // prepare the result to be returned
    auto result = crates->dylib(isolate, name());
    auto okay = result.traits().okay();

    if (result.traits().okay()) okay = thenable->resolve(isolate, result);
    else okay = thenable->reject(isolate, isolate->exception());

    // and resolve to the final details now
    return okay ? thenable : nullptr;
}
