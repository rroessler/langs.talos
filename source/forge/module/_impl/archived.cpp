/// Forge Modules
#include "forge/module/archived.hpp"
#include "forge/crate/service.hpp"
#include "forge/module/service.hpp"
#include "forge/runtime/isolate.hpp"
#include "forge/type/builder.hpp"

/// Metadata Modules
#include "forge/bytecode/metadata.hpp"
#include "forge/type/metadata.hpp"

//  CONSTRUCTORS  //

Forge::Module::Archived::Archived($::Ptr::Unique<Linker::Arena>&& arena) : Abstract<Archived>(arena->resource) {
    arena->resource = resource(), metadata<Phase::COMPILED>()->arena() = std::move(arena);
}

Forge::Module::Archived::Archived(XI::Container* services, $::Ptr::Unique<Linker::Arena>&& arena) :
    Abstract<Archived>(services, arena->resource) {
    arena->resource = resource(), metadata<Phase::COMPILED>()->arena() = std::move(arena);
}

//  PRIVATE METHODS  //

void Forge::Module::Archived::m_parse(XI::Container*, Metadata::Attributes<Phase::PARSED>*) {}
void Forge::Module::Archived::m_compile(XI::Container*, Metadata::Attributes<Phase::COMPILED>*) {}
void Forge::Module::Archived::m_analyze(XI::Container*, Metadata::Attributes<Phase::TYPED>* types) {
    types->context() = $::New().unique<Type::Context>(Type::Builder::object());  // prepare now
}
