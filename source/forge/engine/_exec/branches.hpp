/// Engine Modules
#include "forge/engine/_inline/macros.ipp"

//  PRIVATE METHODS  //

$_INLINE_FORCE Forge::Engine::Mode Forge::Engine::Dispatch::m_jump(Function::Frame* frame, Bytecode::Index index) {
    if ($_UNLIKELY(frame->interrupted())) return Mode::INTERRUPT;  // handle interrupts
    return frame->offset() += frame->constant<Number::Tagged>(index).value(), Mode::NEXT;
}

FORGE_MM_ENGINE_EXECUTE(JUMP_TO, , frame, instruction) { return m_jump(frame, instruction->get<0>()); }

FORGE_MM_ENGINE_EXECUTE(JUMP_FILLED, , frame, instruction) {
    auto value = frame->load(instruction->get<1>());
    if (value.is<Value::Void>()) return Mode::NEXT;
    return m_jump(frame, instruction->get<0>());
}

FORGE_MM_ENGINE_EXECUTE(JUMP_TRUTHY, , frame, instruction) {
    auto value = frame->load(instruction->get<1>());
    if (!value.truthiness()) return Mode::NEXT;
    return m_jump(frame, instruction->get<0>());
}

FORGE_MM_ENGINE_EXECUTE(JUMP_FALSEY, , frame, instruction) {
    auto value = frame->load(instruction->get<1>());
    if (value.truthiness()) return Mode::NEXT;
    return m_jump(frame, instruction->get<0>());
}
