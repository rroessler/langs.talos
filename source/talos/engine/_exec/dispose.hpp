/// Talos Modules
#include "talos/garbage/service.hpp"

/// Engine Modules
#include "talos/engine/_inline/macros.ipp"

/// Value Modules
#include "talos/value/_inline/value.ipp"

//  PRIVATE METHODS  //

TALOS_MM_ENGINE_EXECUTE(DISPOSE_OPEN, isolate, , instruction) {
    return isolate->lifetimes()->open(isolate, instruction->get<0>()), Mode::NEXT;
}

TALOS_MM_ENGINE_EXECUTE(DISPOSE_CLOSE, isolate, , instruction) {
    return isolate->lifetimes()->close(isolate, instruction->get<0>()), Mode::NEXT;
}

TALOS_MM_ENGINE_EXECUTE(DISPOSE_DEFER, isolate, frame, instruction) {
    auto value = frame->load(instruction->get<0>());  // get value
    return isolate->lifetimes()->defer(isolate, value), Mode::NEXT;
}
