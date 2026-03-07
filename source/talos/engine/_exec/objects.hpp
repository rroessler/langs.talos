/// Engine Modules
#include "talos/engine/_inline/macros.ipp"

/// Value Modules
#include "talos/value/_inline/value.ipp"

//  PRIVATE METHODS  //

$_INLINE_FORCE Talos::Value::Any Talos::Engine::Dispatch::m_object(
    Isolate* isolate, const std::span<Value::Any>& pairs) {
    // construct the baseline object instance
    auto object = isolate->create<Object::Instance>();

    // attempt assigning our values now
    for (size_t ii = 0; ii < pairs.size();) {
        auto field = pairs[ii++], value = pairs[ii++];
        auto member = $::New().unique<Member::Reference>(value);
        object.fields()[field.as<Value::Symbol>()] = std::move(member);
    }

    // and return the object that was created
    return object;
}

TALOS_MM_ENGINE_EXECUTE(OBJECT_EMPTY, isolate, frame, instruction) {
    auto object = isolate->create<Object::Instance>();  // construct
    return frame->store(instruction->get<0>(), object), Mode::NEXT;
}

TALOS_MM_ENGINE_EXECUTE(OBJECT_MAKE, isolate, frame, instruction) {
    // construct the outgoing object instance now
    auto object = m_object(isolate, frame->span(instruction->get<1>()));

    // and emplace the resulting object now
    return frame->store(instruction->get<0>(), object), Mode::NEXT;
}
