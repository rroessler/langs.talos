/// Engine Modules
#include "forge/engine/_inline/macros.ipp"

/// Value Modules
#include "forge/iterable/iterator.hpp"
#include "forge/value/_inline/value.ipp"

//  PRIVATE METHODS  //

$_INLINE_FORCE Forge::Value::Any Forge::Engine::Dispatch::m_list(
    Isolate* isolate, const std::span<Value::Any>& values) {
    return isolate->create<Iterable::List>(values);
}

$_INLINE_FORCE Forge::Value::Any Forge::Engine::Dispatch::m_iterator(Isolate* isolate, Value::Any iterable) {
    // check for any immediate iterators (as first-class values)
    if (iterable.is<Iterable::Iterator>()) return iterable;

    auto descriptor = iterable.attribute(Operator::Kind::ITER);  // find via descriptor
    auto iterator = descriptor ? descriptor->getter(isolate, iterable) : Value::Missing();
    return iterator.traits().okay() ? iterator : isolate->panic(6000502, iterable.type_name());
}

FORGE_MM_ENGINE_EXECUTE(LIST_EMPTY, isolate, frame, instruction) {
    auto list = isolate->create<Iterable::List>();  // empty list
    return frame->store(instruction->get<0>(), list), Mode::NEXT;
}

FORGE_MM_ENGINE_EXECUTE(LIST_MAKE, isolate, frame, instruction) {
    auto elements = frame->span(instruction->get<1>());
    auto list = isolate->create<Iterable::List>(elements);
    return frame->store(instruction->get<0>(), list), Mode::NEXT;
}

FORGE_MM_ENGINE_EXECUTE(ITER_LOAD, isolate, frame, instruction) {
    auto slot = instruction->get<0>();  // final slot
    auto iterable = frame->load(instruction->get<1>());
    auto iterator = m_iterator(isolate, iterable);
    if (!iterator.traits().okay()) return Mode::PANIC;
    return frame->store(slot, iterator), Mode::NEXT;
}

FORGE_MM_ENGINE_EXECUTE(ITER_NEXT, isolate, frame, instruction) {
    auto slot = instruction->get<0>();
    auto value = instruction->get<1>();
    auto index = instruction->get<2>();

    auto iterator = frame->load<Iterable::Iterator>(slot);
    auto result = iterator.done() || !iterator.okay();
    if (!result) result = iterator.next(isolate);
    if (!iterator.okay()) return Mode::PANIC;

    // update the current details to be used
    if (!value.nowhere()) frame->store(value, iterator.value());
    if (!index.nowhere()) frame->store(index, Number::Tagged(iterator.index() - 1));

    // and allow jumping based on the done-state
    return frame->accumulator() = Value::Boolean(result), Mode::NEXT;
}
