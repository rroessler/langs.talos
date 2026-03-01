/// Forge Modules
#include <forge/heap/service.hpp>
#include <forge/member/factory.hpp>

/// Assert Modules
#include <forge/builtins/_inline/assert.ipp>

/// Crate Modules
#include "crates/memory/source/module.hpp"

//  PROPERTIES  //

/// @brief The underlying memory addon installer.
FORGE_MM_DYLIB_ADDON(Memory, CRATE_XX_MEMORY_METHODS)

//  PRIVATE METHODS  //

FORGE_MM_DYLIB_METHOD(Memory, heap_total, isolate, ) {
    return Number::Tagged(isolate->service<Heap::Service>()->total());
}

FORGE_MM_DYLIB_METHOD(Memory, heap_avail, isolate, ) {
    return Number::Tagged(isolate->service<Heap::Service>()->available());
}

FORGE_MM_DYLIB_METHOD(Memory, heap_usage, isolate, ) {
    return Number::Tagged(isolate->service<Heap::Service>()->usage());
}
