/// Talos Modules
#include "talos/module/archived.hpp"
#include "talos/crate/service.hpp"
#include "talos/module/service.hpp"
#include "talos/runtime/isolate.hpp"
#include "talos/type/builder.hpp"

/// Metadata Modules
#include "talos/bytecode/metadata.hpp"
#include "talos/type/metadata.hpp"

//  CONSTRUCTORS  //

Talos::Module::Archived::Archived($::Ptr::Unique<Linker::Arena>&& arena) : Abstract<Archived>(arena->resource) {
    arena->resource = resource(), metadata<Phase::COMPILED>()->arena() = std::move(arena);
}

Talos::Module::Archived::Archived(XI::Container* services, $::Ptr::Unique<Linker::Arena>&& arena) :
    Abstract<Archived>(services, arena->resource) {
    arena->resource = resource(), metadata<Phase::COMPILED>()->arena() = std::move(arena);
}

//  PRIVATE METHODS  //

void Talos::Module::Archived::m_parse(XI::Container*, Metadata::Attributes<Phase::PARSED>*) {}
void Talos::Module::Archived::m_compile(XI::Container*, Metadata::Attributes<Phase::COMPILED>*) {}
void Talos::Module::Archived::m_analyze(XI::Container*, Metadata::Attributes<Phase::TYPED>* types) {
    types->context() = $::New().unique<Type::Context>(Type::Builder::object());  // prepare now
}
