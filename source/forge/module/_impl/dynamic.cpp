/// Forge Modules
#include "forge/module/dynamic.hpp"
#include "forge/crate/service.hpp"
#include "forge/runtime/isolate.hpp"
#include "forge/type/builder.hpp"

/// Metadata Modules
#include "forge/engine/metadata.hpp"
#include "forge/type/metadata.hpp"

//  PRIVATE METHODS  //

void Forge::Module::Dynamic::m_parse(XI::Container*, Metadata::Attributes<Phase::PARSED>*) {}
void Forge::Module::Dynamic::m_analyze(XI::Container*, Metadata::Attributes<Phase::TYPED>* types) {
    types->context() = $::New().unique<Type::Context>(Type::Builder::object());  // prepare now
}

void Forge::Module::Dynamic::m_compile(XI::Container*, Metadata::Attributes<Phase::COMPILED>*) {}

Forge::Async::Thenable* Forge::Module::Dynamic::m_interpret(
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
