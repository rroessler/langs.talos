/// Talos Includes
#include "talos/module/archive.hpp"
#include "talos/bytecode/metadata.hpp"
#include "talos/image/arena.hpp"
#include "talos/runtime/container.hpp"

//  CONSTRUCTORS  //

Talos::Module::Archive::Archive($::Unique::Pointer<Image::Arena> &&arena) :
    Archive($::Global::get<Runtime::Container>(), std::move(arena)) {}

Talos::Module::Archive::Archive(XI::Container *services, $::Unique::Pointer<Image::Arena> &&arena) :
    Mixin(services, arena->resource.buffer()) {
  arena->resource = resource(); // update the resource
  metadata<Phase::COMPILED>()->arena() = std::move(arena);
}
