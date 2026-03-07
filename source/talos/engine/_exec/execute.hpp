/// Talos Modules
#include "talos/signal/service.hpp"

/// Engine Modules
#include "talos/engine/_inline/macros.ipp"

//  PRIVATE METHODS  //

TALOS_MM_ENGINE_EXECUTE(EXEC_INVALID, , , ) { $::System::unreachable(); }

TALOS_MM_ENGINE_EXECUTE(EXEC_NOOP, , , ) { return Mode::NEXT; }
TALOS_MM_ENGINE_EXECUTE(EXEC_RETURN, , , ) { return Mode::RETURN; }
TALOS_MM_ENGINE_EXECUTE(EXEC_CANCEL, , , ) { return Mode::INTERRUPT; }
TALOS_MM_ENGINE_EXECUTE(EXEC_ABORT, isolate, , instruction) { isolate->thread()->shutdown(instruction->get<0>()); }
TALOS_MM_ENGINE_EXECUTE(EXEC_PANIC, isolate, frame, ) { return isolate->panic(frame->accumulator()), Mode::PANIC; }

TALOS_MM_ENGINE_EXECUTE(EXEC_RAISE, isolate, , instruction) {
    auto code = static_cast<Signal::Code>(instruction->get<0>().encode());
    return isolate->service<Signal::Service>()->raise(code), Mode::NEXT;
}
