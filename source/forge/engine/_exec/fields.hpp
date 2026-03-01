/// Engine Modules
#include "forge/engine/_inline/macros.ipp"

//  PRIVATE METHODS  //

FORGE_MM_ENGINE_EXECUTE(LOAD_FIELD, isolate, frame, instruction) {
    auto target = frame->load(instruction->get<1>());  // prepare target
    auto field = m_getter(isolate, frame, target, instruction->get<2>());
    if ($_UNLIKELY(!field.traits().okay())) return Mode::PANIC;
    return frame->store(instruction->get<0>(), field), Mode::NEXT;
}

FORGE_MM_ENGINE_EXECUTE(STORE_FIELD, isolate, frame, instruction) {
    auto value = frame->load(instruction->get<1>());
    auto target = frame->load(instruction->get<0>());
    auto field = m_setter(isolate, frame, target, value, instruction->get<2>());
    return $_LIKELY(field.traits().okay()) ? Mode::NEXT : Mode::PANIC;
}
