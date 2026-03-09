/// Talos Modules
#include "talos/runtime/isolate.hpp"
#include "talos/signal/service.hpp"

/// Inline Modules
#include "talos/machine/_inline/macros.ipp"

/// Forward Declarations
$_FWD(Talos::Machine::Dispatch, void abort(Runtime::Isolate *, int32_t))
$_FWD(Talos::Machine::Dispatch, void raise(Runtime::Isolate *, int32_t))
$_FWD(Talos::Machine::Dispatch, void panic(Runtime::Isolate *, Reference))

//  PUBLIC METHODS  //

void Talos::Machine::Dispatch::abort(Runtime::Isolate *isolate, int32_t code) { isolate->thread()->shutdown(code); }
void Talos::Machine::Dispatch::panic(Runtime::Isolate *isolate, Reference value) { isolate->panic(Value::Any(value)); }
void Talos::Machine::Dispatch::raise(Runtime::Isolate *isolate, int32_t code) {
    isolate->service<Signal::Service>()->raise(static_cast<Signal::Code>(code));
}

//  PRIVATE METHODS  //

TALOS_MM_MACHINE_EMIT(EXEC_INVALID, , ) { $::System::unreachable(); }

TALOS_MM_MACHINE_EMIT(EXEC_NOOP, builder, ) { __ee__ noop(); }
TALOS_MM_MACHINE_EMIT(EXEC_RETURN, builder, ) { __ee__ returns(); }
TALOS_MM_MACHINE_EMIT(EXEC_CANCEL, builder, ) { __ee__ interrupt(); }

TALOS_MM_MACHINE_EMIT(EXEC_ABORT, builder, instruction) {
    __ee__ invoke(Dispatch::abort, builder->isolate, instruction->get<0>().encode());
}

TALOS_MM_MACHINE_EMIT(EXEC_RAISE, builder, instruction) {
    __ee__ invoke(Dispatch::raise, builder->isolate, instruction->get<0>().encode());
}

TALOS_MM_MACHINE_EMIT(EXEC_PANIC, builder, ) {
    auto tx = __ee__ resolve(Engine::Accumulator());
    __ee__ invoke(Dispatch::panic, builder->isolate, tx);
    __ee__ returns(Value::Failure());  // and force exit
}
