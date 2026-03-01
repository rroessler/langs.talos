/// Forge Modules
#include "forge/engine/dispatch.hpp"
#include "forge/iterable/list.hpp"
#include "forge/runtime/isolate.hpp"
#include "forge/value/boolean.hpp"

/// Inline Modules
#include "forge/machine/_inline/macros.ipp"

/// Forward Declarations
$_FWD(static Reference empty(Runtime::Isolate*), Forge::Machine::Dispatch)
$_FWD(Reference list(Runtime::Isolate*, Value::Any*), Forge::Machine::Dispatch)

$_FWD(Reference value(Reference), Forge::Machine::Dispatch)
$_FWD(Reference index(Reference), Forge::Machine::Dispatch)
$_FWD(Reference bump(Runtime::Isolate*, Reference), Forge::Machine::Dispatch)

//  PUBLIC METHODS  //

Forge::Machine::Reference Forge::Machine::Dispatch::empty(Runtime::Isolate* isolate) {
    return isolate->create<Iterable::List>().pointer();
}

Forge::Machine::Reference Forge::Machine::Dispatch::list(Runtime::Isolate* isolate, Value::Any* span) {
    return Engine::Dispatch::list(isolate, Template::arguments(span));
}

Forge::Machine::Reference Forge::Machine::Dispatch::value(Reference iterable) {
    return Value::Cast<Iterable::Iterator>(iterable).value().pointer();
}

Forge::Machine::Reference Forge::Machine::Dispatch::index(Reference iterable) {
    return Number::Tagged(Value::Cast<Iterable::Iterator>(iterable).index() - 1).pointer();
}

Forge::Machine::Reference Forge::Machine::Dispatch::bump(Runtime::Isolate* isolate, Reference iterable) {
    // load the incoming iterator to be bumped
    auto iterator = Value::Cast<Iterable::Iterator>(iterable);

    // get the resulting and handle as needed
    auto result = iterator.done() || !iterator.okay();
    if (!result) result = iterator.next(isolate);

    // and return a suitable result now as needed
    return iterator.okay() ? Value::Boolean(result).pointer() : Value::Failure().pointer();
}

//  PRIVATE METHODS  //

FORGE_MM_MACHINE_EMIT(LIST_EMPTY, builder, instruction) {
    auto dx = __ee__ resolve(instruction->get<0>());
    __ee__ invoke(Dispatch::empty, dx, builder->isolate);
}

FORGE_MM_MACHINE_EMIT(LIST_MAKE, builder, instruction) {
    // prepare the necessary registers to be used
    auto dx = __ee__ resolve(instruction->get<0>());

    // ensure we preload the necessary parameters
    __ee__ parameters(instruction->get<1>());

    // and invoke the incoming list constructor
    __ee__ invoke(Dispatch::list, dx, builder->isolate, builder->stack);
}

FORGE_MM_MACHINE_EMIT(ITER_LOAD, builder, instruction) {
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

FORGE_MM_MACHINE_EMIT(ITER_NEXT, builder, instruction) {
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
