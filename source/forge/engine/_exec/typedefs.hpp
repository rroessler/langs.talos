/// Forge Modules
#include "forge/object/class.hpp"
#include "forge/object/enum.hpp"
#include "forge/value/boolean.hpp"

/// Engine Modules
#include "forge/engine/_inline/macros.ipp"

//  PRIVATE METHODS  //

$_INLINE_FORCE Forge::Value::Any Forge::Engine::Dispatch::m_ensure(
    Isolate* isolate, Value::Any value, Value::Any guard) {
    switch (m_extends(value, guard)) {
        case Subtype::SUCCESS: return value;  // full match for our value here
        case Subtype::MISMATCH: return isolate->panic(3000353, guard.type_name());
        default: return isolate->panic(3000352, value.type_name(), guard.as<Object::Class>().name().view());
    }
}

$_INLINE_FORCE Forge::Engine::Subtype Forge::Engine::Dispatch::m_extends(Value::Any value, Value::Any guard) {
    // check if we require a specialized handler
    auto classical = guard.is<Object::Class>();

    // check immediately for extension types
    if (classical) return guard.as<Object::Class>().extends(value) ? Subtype::SUCCESS : Subtype::FAILURE;

    // check for enumeration types now
    if (guard.is<Object::Enum>()) return value == guard ? Subtype::SUCCESS : Subtype::FAILURE;

    // otherwise we need to handle with some special cases now
    return guard.is<Value::Void>() && value.is<Value::Void>() ? Subtype::SUCCESS : Subtype::MISMATCH;
}

FORGE_MM_ENGINE_EXECUTE(TYPE_CAST, isolate, frame, instruction) {
    // get both the value and the guard now
    auto value = frame->load(instruction->get<1>());
    auto guard = frame->load(instruction->get<2>());

    // get the result now
    auto result = m_ensure(isolate, value, guard);

    // and return the necessary details
    if (!result.traits().okay()) return Mode::PANIC;
    return frame->store(instruction->get<0>(), result), Mode::NEXT;
}

FORGE_MM_ENGINE_EXECUTE(TYPE_GUARD, , frame, instruction) {
    // prepare the destination to be used
    auto destination = instruction->get<0>();

    // get both the value and the guard now
    auto value = frame->load(instruction->get<1>());
    auto guard = frame->load(instruction->get<2>());

    // check if we have some valid extensions now
    auto extends = m_extends(value, guard) == Subtype::SUCCESS;

    // and resolve the value to be shown now
    return frame->store(destination, Value::Boolean(extends)), Mode::NEXT;
}