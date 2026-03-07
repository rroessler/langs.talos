/// Talos Modules
#include "talos/member/factory.hpp"

/// Engine Modules
#include "talos/engine/_inline/macros.ipp"

/// Value Modules
#include "talos/value/_inline/value.ipp"

//  PRIVATE METHODS  //

TALOS_MM_ENGINE_EXECUTE(CLASS_BIND, isolate, frame, instruction) {
    // resolve the underlying constructor and bind it to the class
    auto* info = frame->arena()->functions.at(instruction->get<1>()).get();
    auto closure = isolate->create<Function::Closure>(info, frame->context());

    // attempt resolving the incoming class prototype now
    auto prototype = frame->load<Object::Class>(instruction->get<0>());

    // prepare the constructor details
    auto symbol = Operator::Attribute::CALL;
    auto member = Member::Factory::reference(closure);

    // attempt binding the prototype now
    auto bound = prototype.statics().try_emplace(symbol, std::move(member)).second;

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
