/// Machine Includes
#include "talos/machine/_inline/macros.ipp"

//  EMITTER METHODS  //

TALOS_MM_MACHINE_EMIT(LOAD_CONTEXT, builder, instruction) { __ee__ load(instruction); }
TALOS_MM_MACHINE_EMIT(STORE_CONTEXT, builder, instruction) { __ee__ move(instruction); }
TALOS_MM_MACHINE_EMIT(LOAD_UPVALUE, builder, instruction) { __ee__ load(instruction, instruction->get<2>()); }
TALOS_MM_MACHINE_EMIT(STORE_UPVALUE, builder, instruction) { __ee__ move(instruction, instruction->get<2>()); }
