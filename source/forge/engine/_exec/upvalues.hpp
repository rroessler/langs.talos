/// Engine Modules
#include "forge/engine/_inline/macros.ipp"

//  PRIVATE METHODS  //

FORGE_MM_ENGINE_EXECUTE(LOAD_CONTEXT, , frame, instruction) {
    auto value = frame->context().load(instruction->get<1>());
    return frame->store(instruction->get<0>(), value), Mode::NEXT;
}

FORGE_MM_ENGINE_EXECUTE(STORE_CONTEXT, , frame, instruction) {
    auto value = frame->load(instruction->get<1>());  // get the value now
    return frame->context().store(instruction->get<0>(), value), Mode::NEXT;
}

FORGE_MM_ENGINE_EXECUTE(LOAD_UPVALUE, , frame, instruction) {
    auto slot = instruction->get<1>();
    auto depth = instruction->get<2>();
    auto value = frame->context(depth).load(slot);
    return frame->store(instruction->get<0>(), value), Mode::NEXT;
}

FORGE_MM_ENGINE_EXECUTE(STORE_UPVALUE, , frame, instruction) {
    auto slot = instruction->get<0>();
    auto depth = instruction->get<2>();
    auto value = frame->load(instruction->get<1>());
    return frame->context(depth).store(slot, value), Mode::NEXT;
}
