/// Engine Modules
#include "forge/engine/_inline/macros.ipp"

//  PRIVATE METHODS  //

FORGE_MM_ENGINE_EXECUTE(REG_MOVE, , frame, instruction) {
    auto value = frame->load(instruction->get<1>());  // prepare
    return frame->store(instruction->get<0>(), value), Mode::NEXT;
}

FORGE_MM_ENGINE_EXECUTE(REG_SWAP, , frame, instruction) {
    auto ax = instruction->get<0>();
    auto bx = instruction->get<1>();
    auto* stack = frame->stack();
    std::swap(stack[ax], stack[bx]);
    return Mode::NEXT;  // valid swap
}
