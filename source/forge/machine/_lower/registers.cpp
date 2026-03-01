/// Inline Modules
#include "forge/machine/_inline/macros.ipp"

//  PRIVATE METHODS  //

FORGE_MM_MACHINE_EMIT(REG_MOVE, builder, instruction) { __ee__ move(instruction->get<0>(), instruction->get<1>()); }

FORGE_MM_MACHINE_EMIT(REG_SWAP, builder, instruction) {
    auto tx = __cc__ new_gp64("@tx");  // temporary
    auto ax = __ee__ resolve(instruction->get<0>());
    auto bx = __ee__ resolve(instruction->get<1>());

    // swap via a total of moves to be used
    __cc__ mov(tx, ax);
    __cc__ mov(ax, bx);
    __cc__ mov(bx, tx);
}
