/// Machine Includes
#include "talos/machine/_inline/macros.ipp"

//  EMITTER METHODS  //

TALOS_MM_MACHINE_EMIT(REG_MOVE, builder, instruction) { __ee__ move(instruction->get<0>(), instruction->get<1>()); }
TALOS_MM_MACHINE_EMIT(REG_SWAP, builder, instruction) { __ee__ swap(instruction->get<0>(), instruction->get<1>()); }
