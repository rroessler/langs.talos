/// Talos Modules
#include "talos/member/factory.hpp"
#include "talos/operator/traits.hpp"

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

TALOS_MM_ENGINE_EXECUTE(OBJECT_ATTR, isolate, frame, instruction) {
    // resolve the callback to be bound
    auto callback = frame->load(instruction->get<0>());
    auto target = frame->load(instruction->get<1>());

    // ensure the callback is valid
    if (!callback.is<Function::Dynamic>()) return isolate->panic(6000200, callback.type_name()), Mode::PANIC;

    // resolve the expected kind to be emitted
    auto kind = static_cast<Operator::Kind>(instruction->get<2>().encode());

    // resolve a suitable target for overloading
    auto name = Operator::Traits::name(kind);
    auto symbol = Operator::Traits::symbol(kind);

    // ensure we have a valid target for updating
    if (!target.is<Object::Instance>()) return isolate->panic(6000302, name, target.type_name()), Mode::PANIC;

    // get the underlying instance now
    auto& fields = target.as<Object::Instance>().fields();

    // check if the field has already been assigned
    if (fields.contains(symbol)) return isolate->panic(6000303, name, target.type_name()), Mode::PANIC;

    // can safely assign the necessary attribute now
    return fields.emplace(symbol, Member::Factory::reference(callback)), Mode::NEXT;
}
