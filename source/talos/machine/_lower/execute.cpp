/// Machine Includes
#include "talos/machine/_inline/macros.ipp"

//  EMITTER METHODS  //

TALOS_MM_MACHINE_EMIT(EXEC_NOOP, , ) { $_ABORT("Unreachable Bytecode Operation 'EXEC_NOOP'"); }
TALOS_MM_MACHINE_EMIT(EXEC_INVALID, , ) { $_ABORT("Unreachable Bytecode Operation 'EXEC_INVALID'"); }

TALOS_MM_MACHINE_EMIT(EXEC_RETURN, builder, ) { __ee__ ret(); }
TALOS_MM_MACHINE_EMIT(EXEC_CANCEL, builder, ) { __ee__ irq(); }

TALOS_MM_MACHINE_EMIT(EXEC_ABORT, builder, instruction) {
  auto errc = instruction->get<0>().encode();
  __ee__ call(Glue::abort, builder->isolate, errc);
}

TALOS_MM_MACHINE_EMIT(EXEC_RAISE, builder, instruction) {
  auto code = instruction->get<0>().encode();
  __ee__ call(Glue::raise, builder->isolate, code);
}

TALOS_MM_MACHINE_EMIT(EXEC_PANIC, builder, ) {
  auto tx = __ee__ slot(Register::Accumulator);
  __ee__ call(Glue::panic, builder->isolate, tx);
  __ee__ ret(Constants::Fail); // force failure
}
