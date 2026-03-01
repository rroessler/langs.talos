/// Forge Modules
#include "forge/signal/service.hpp"

/// Engine Modules
#include "forge/engine/_inline/macros.ipp"

//  PRIVATE METHODS  //

FORGE_MM_ENGINE_EXECUTE(EXEC_INVALID, , , ) { $::System::unreachable(); }

FORGE_MM_ENGINE_EXECUTE(EXEC_NOOP, , , ) { return Mode::NEXT; }
FORGE_MM_ENGINE_EXECUTE(EXEC_RETURN, , , ) { return Mode::RETURN; }
FORGE_MM_ENGINE_EXECUTE(EXEC_CANCEL, , , ) { return Mode::INTERRUPT; }
FORGE_MM_ENGINE_EXECUTE(EXEC_ABORT, isolate, , instruction) { isolate->thread()->shutdown(instruction->get<0>()); }
FORGE_MM_ENGINE_EXECUTE(EXEC_PANIC, isolate, frame, ) { return isolate->panic(frame->accumulator()), Mode::PANIC; }

FORGE_MM_ENGINE_EXECUTE(EXEC_RAISE, isolate, , instruction) {
    auto code = static_cast<Signal::Code>(instruction->get<0>().encode());
    return isolate->service<Signal::Service>()->raise(code), Mode::NEXT;
}
