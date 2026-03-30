/// Talos Modules
#include <talos/heap/service.hpp>
#include <talos/member/factory.hpp>

/// Assert Modules
#include <talos/builtins/_inline/assert.ipp>

/// Crate Modules
#include "crates/mem/source/module.hpp"

//  PROPERTIES  //

/// @brief The underlying memory addon installer.
TALOS_MM_DYLIB_ADDON(Memory, CRATE_XX_MEMORY_METHODS)

//  PRIVATE METHODS  //

TALOS_MM_DYLIB_METHOD(Memory, heap_total, isolate, ) {
    return Number::Tagged(isolate->service<Heap::Service>()->total());
}

TALOS_MM_DYLIB_METHOD(Memory, heap_avail, isolate, ) {
    return Number::Tagged(isolate->service<Heap::Service>()->available());
}

TALOS_MM_DYLIB_METHOD(Memory, heap_usage, isolate, ) {
    return Number::Tagged(isolate->service<Heap::Service>()->usage());
}

TALOS_MM_DYLIB_METHOD(Memory, thread_total, isolate, ) { return Number::Tagged(isolate->thread()->stack()->size()); }

TALOS_MM_DYLIB_METHOD(Memory, thread_avail, isolate, ) {
    return Number::Tagged(isolate->thread()->stack()->remaining());
}

TALOS_MM_DYLIB_METHOD(Memory, thread_usage, isolate, ) {
    const auto* stack = isolate->thread()->stack();
    return Number::Tagged(stack->size() - stack->remaining());
}
