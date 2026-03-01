/// Engine Modules
#include "forge/engine/_inline/macros.ipp"

//  PRIVATE METHODS  //

$_INLINE_FORCE Forge::Value::Any Forge::Engine::Dispatch::m_concat(
    Isolate* isolate, Value::Any left, Value::Any right) {
    // get the incoming views to be used
    auto lv = left.as<String::Dynamic>();
    auto rv = right.as<String::Dynamic>();

    // construct the resulting string-buffer now
    return String::Dynamic(isolate, "{0}{1}", lv, rv);
}

FORGE_MM_ENGINE_EXECUTE(STRING_MAKE, isolate, frame, instruction) {
    auto intern = frame->intern(instruction->get<1>());
    auto string = String::Dynamic(isolate, intern);
    return frame->store(instruction->get<0>(), string), Mode::NEXT;
}

FORGE_MM_ENGINE_EXECUTE(STRING_CONCAT, isolate, frame, instruction) {
    auto left = frame->load(instruction->get<1>()), right = frame->load(instruction->get<2>());
    return frame->store(instruction->get<0>(), m_concat(isolate, left, right)), Mode::NEXT;
}
