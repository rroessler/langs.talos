/// Engine Modules
#include "talos/engine/_inline/macros.ipp"

/// Value Modules
#include "talos/value/_inline/value.ipp"

//  PRIVATE METHODS  //

TALOS_MM_ENGINE_EXECUTE(CLASS_EXPORT, isolate, frame, instruction) {
    // get the underlying name and value now
    auto value = frame->load(instruction->get<0>());
    auto name = frame->intern(instruction->get<1>());

    // prepare the reference instance to be used
    auto reference = $::New().unique<Member::Reference>(value, instruction->get<2>());

    // get the baseline self value now to be used
    auto self = frame->self().as<Object::Instance>();

    // get the underlying field to be updated now
    if (self.fields().try_emplace(name.symbol(), std::move(reference)).second) return Mode::NEXT;

    // failed to emplace, so lets declare an error here
    return isolate->panic(6000801, name, self.name()), Mode::PANIC;
}

TALOS_MM_ENGINE_EXECUTE(CLASS_BIND, isolate, frame, instruction) {
    // attempt resolving the incoming class prototype now
    auto prototype = frame->load<Object::Class>(instruction->get<0>());

    // resolve the underlying constructor and bind it to the class
    auto* info = frame->arena()->functions.at(instruction->get<1>()).get();
    auto closure = isolate->create<Function::Closure>(info, prototype, frame->context());

    // prepare the constructor details
    static constexpr auto s_symbol = Operator::Attribute::CALL;
    auto member = $::New().unique<Member::Reference>(closure);

    // attempt binding the prototype now
    auto bound = prototype.statics().try_emplace(s_symbol, std::move(member)).second;

    // and resolve as necessary now
    return bound ? Mode::NEXT : (isolate->panic(6000800, prototype.type_name()), Mode::PANIC);
}

TALOS_MM_ENGINE_EXECUTE(CLASS_MAKE, isolate, frame, instruction) {
    // pull out the underlying slot and parent
    auto slot = instruction->get<0>();
    auto extends = frame->load(slot);

    // then also resolve the name and shape
    auto name = frame->intern(instruction->get<1>());
    Shape::Underlying shape = instruction->get<2>();

    // construct a current class prototype now
    auto prototype = isolate->create<Object::Class>(name.view(), shape, extends);

    // and bind the prototype to the extension output
    return frame->store(slot, prototype), Mode::NEXT;
}
