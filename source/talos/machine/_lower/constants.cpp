/// Machine Includes
#include "talos/machine/_inline/macros.ipp"

//  EMITTER METHODS  //

TALOS_MM_MACHINE_EMIT(LOAD_SELF, builder, instruction) { __ee__ self(instruction->get<0>()); }
TALOS_MM_MACHINE_EMIT(LOAD_ZERO, builder, instruction) { __ee__ load(instruction->get<0>(), Number::Zero); }
TALOS_MM_MACHINE_EMIT(LOAD_ONE, builder, instruction) { __ee__ load(instruction->get<0>(), Number::One); }
TALOS_MM_MACHINE_EMIT(LOAD_VOID, builder, instruction) { __ee__ load(instruction->get<0>(), Constants::Void); }
TALOS_MM_MACHINE_EMIT(LOAD_TRUE, builder, instruction) { __ee__ load(instruction->get<0>(), Value::True); }
TALOS_MM_MACHINE_EMIT(LOAD_FALSE, builder, instruction) { __ee__ load(instruction->get<0>(), Value::False); }

TALOS_MM_MACHINE_EMIT(LOAD_CONST, builder, instruction) {
  auto index = instruction->get<1>();
  auto *arena = builder->info->arena();
  auto constant = arena->constants[index];
  __ee__ load(instruction->get<0>(), constant);
}

TALOS_MM_MACHINE_EMIT(LOAD_GLOBAL, builder, instruction) {
  // get some details about the load
  auto index = instruction->get<1>();
  auto *arena = builder->info->arena();

  // prepare the symbol and destination arguments
  auto sx = __ee__ ref(arena->constants[index]);
  auto dx = __ee__ slot(instruction->get<0>());

  // call the global getter with our arguments
  __ee__ call(Glue::global, dx, builder->isolate, sx);
}
