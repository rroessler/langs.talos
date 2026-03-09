/// Talos Modules
#include "talos/engine/dispatch.hpp"
#include "talos/iterable/list.hpp"
#include "talos/runtime/isolate.hpp"
#include "talos/value/boolean.hpp"

/// Inline Modules
#include "talos/machine/_inline/macros.ipp"

/// Forward Declarations
$_FWD(Talos::Machine::Dispatch, static Reference empty(Runtime::Isolate*))
$_FWD(Talos::Machine::Dispatch, Reference list(Runtime::Isolate*, Value::Any*))

$_FWD(Talos::Machine::Dispatch, Reference value(Reference))
$_FWD(Talos::Machine::Dispatch, Reference index(Reference))
$_FWD(Talos::Machine::Dispatch, Reference bump(Runtime::Isolate*, Reference))

//  PUBLIC METHODS  //

Talos::Machine::Reference Talos::Machine::Dispatch::empty(Runtime::Isolate* isolate) {
    return isolate->create<Iterable::List>().pointer();
}

Talos::Machine::Reference Talos::Machine::Dispatch::list(Runtime::Isolate* isolate, Value::Any* span) {
    return Engine::Dispatch::list(isolate, Template::arguments(span));
}

Talos::Machine::Reference Talos::Machine::Dispatch::value(Reference iterable) {
    return Value::Cast<Iterable::Iterator>(iterable).value().pointer();
}

Talos::Machine::Reference Talos::Machine::Dispatch::index(Reference iterable) {
    return Number::Tagged(Value::Cast<Iterable::Iterator>(iterable).index() - 1).pointer();
}

Talos::Machine::Reference Talos::Machine::Dispatch::bump(Runtime::Isolate* isolate, Reference iterable) {
    // load the incoming iterator to be bumped
    auto iterator = Value::Cast<Iterable::Iterator>(iterable);

    // get the resulting and handle as needed
    auto result = iterator.done() || !iterator.okay();
    if (!result) result = iterator.next(isolate);

    // and return a suitable result now as needed
    return iterator.okay() ? Value::Boolean(result).pointer() : Value::Failure().pointer();
}

//  PRIVATE METHODS  //

TALOS_MM_MACHINE_EMIT(LIST_EMPTY, builder, instruction) {
    auto dx = __ee__ resolve(instruction->get<0>());
    __ee__ invoke(Dispatch::empty, dx, builder->isolate);
}

TALOS_MM_MACHINE_EMIT(LIST_MAKE, builder, instruction) {
    // prepare the necessary registers to be used
    auto dx = __ee__ resolve(instruction->get<0>());

    // ensure we preload the necessary parameters
    __ee__ parameters(instruction->get<1>());

    // and invoke the incoming list constructor
    __ee__ invoke(Dispatch::list, dx, builder->isolate, builder->stack);
}

TALOS_MM_MACHINE_EMIT(ITER_LOAD, builder, instruction) {
    // prepare the necessary slots
    auto dv = instruction->get<0>();
    auto iterable = instruction->get<1>();

    // and the necessary registers
    auto dx = __ee__ resolve(dv);
    auto ix = __ee__ resolve(iterable);

    // attempt loading the iterator now
    __ee__ invoke(Engine::Dispatch::iterator, dx, builder->isolate, ix);

    // run some post validation as well
    __ee__ validate(dx, Validate::FAST);
}

TALOS_MM_MACHINE_EMIT(ITER_NEXT, builder, instruction) {
    // prepare the necessary slots
    auto value = instruction->get<1>();
    auto index = instruction->get<2>();
    auto iterator = instruction->get<0>();

    // prepare the registers to be used now
    auto dx = __cc__ new_gp64("@dx");
    auto ix = __ee__ resolve(iterator);

    // attempt bumping the iterator
    __ee__ invoke(Dispatch::bump, dx, builder->isolate, ix);

    // ensure the incoming result is valid now (only expect one type of failure to occur)
    __cc__ j(builder->panic, asmjit::ujit::cmp_eq(dx, __iv__(Value::Failure())));

    // finally update the resulting value/index
    if (!value.nowhere()) __ee__ invoke(Dispatch::value, __ee__ resolve(value), ix);
    if (!index.nowhere()) __ee__ invoke(Dispatch::index, __ee__ resolve(index), ix);

    // update the accumulator with the result
    __ee__ move(Engine::Accumulator(), dx);
}
