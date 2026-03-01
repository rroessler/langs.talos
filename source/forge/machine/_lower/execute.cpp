/// Forge Modules
#include "forge/runtime/isolate.hpp"
#include "forge/signal/service.hpp"

/// Inline Modules
#include "forge/machine/_inline/macros.ipp"

/// Forward Declarations
$_FWD(void abort(Runtime::Isolate *, int32_t), Forge::Machine::Dispatch)
$_FWD(void raise(Runtime::Isolate *, int32_t), Forge::Machine::Dispatch)
$_FWD(void panic(Runtime::Isolate *, Reference), Forge::Machine::Dispatch)

//  PUBLIC METHODS  //

void Forge::Machine::Dispatch::abort(Runtime::Isolate *isolate, int32_t code) { isolate->thread()->shutdown(code); }
void Forge::Machine::Dispatch::panic(Runtime::Isolate *isolate, Reference value) { isolate->panic(Value::Any(value)); }
void Forge::Machine::Dispatch::raise(Runtime::Isolate *isolate, int32_t code) {
    isolate->service<Signal::Service>()->raise(static_cast<Signal::Code>(code));
}

//  PRIVATE METHODS  //

FORGE_MM_MACHINE_EMIT(EXEC_INVALID, , ) { $::System::unreachable(); }

FORGE_MM_MACHINE_EMIT(EXEC_NOOP, builder, ) { __ee__ noop(); }
FORGE_MM_MACHINE_EMIT(EXEC_RETURN, builder, ) { __ee__ returns(); }
FORGE_MM_MACHINE_EMIT(EXEC_CANCEL, builder, ) { __ee__ interrupt(); }

FORGE_MM_MACHINE_EMIT(EXEC_ABORT, builder, instruction) {
    __ee__ invoke(Dispatch::abort, builder->isolate, instruction->get<0>().encode());
}

FORGE_MM_MACHINE_EMIT(EXEC_RAISE, builder, instruction) {
    __ee__ invoke(Dispatch::raise, builder->isolate, instruction->get<0>().encode());
}

FORGE_MM_MACHINE_EMIT(EXEC_PANIC, builder, ) {
    auto tx = __ee__ resolve(Engine::Accumulator());
    __ee__ invoke(Dispatch::panic, builder->isolate, tx);
    __ee__ returns(Value::Failure());  // and force exit
}
