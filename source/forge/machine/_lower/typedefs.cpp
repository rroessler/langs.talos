/// Forge Modules
#include "forge/engine/dispatch.hpp"
#include "forge/value/boolean.hpp"

/// Inline Modules
#include "forge/machine/_inline/macros.ipp"

//  PRIVATE METHODS  //

FORGE_MM_MACHINE_EMIT(TYPE_CAST, builder, instruction) {
    // prepare the registers to be used
    auto dv = instruction->get<0>();
    auto value = instruction->get<1>();
    auto guard = instruction->get<2>();

    // prepare the output registers now
    auto dx = __ee__ resolve(dv);
    auto vx = __ee__ resolve(value);
    auto gx = __ee__ resolve(guard);

    // attempt invoking the type-cast handler
    __ee__ invoke(Engine::Dispatch::ensure, dx, builder->isolate, vx, gx);

    // and fast-exit depending on the result
    __ee__ validate(dx, Validate::FAST);
}

FORGE_MM_MACHINE_EMIT(TYPE_GUARD, builder, instruction) {
    // otherwise we check the incoming extension details
    auto dv = instruction->get<0>();
    auto value = instruction->get<1>();
    auto guard = instruction->get<2>();

    // prepare the output registers now
    auto dx = __ee__ resolve(dv);
    auto vx = __ee__ resolve(value);
    auto gx = __ee__ resolve(guard);
    auto tx = __cc__ new_gp64("@tx");

    // prepare a label for setting a result
    auto bail = __cc__ new_label();

    // attempt getting the extension result
    __ee__ invoke(Engine::Dispatch::extends, tx, vx, gx);

    // set the baseline result now
    __ee__ load(dx, Value::Boolean(false));

    // convert the resulting to a boolean now
    __cc__ j(bail, asmjit::ujit::cmp_ne(tx, Engine::Subtype::SUCCESS));

    // if we did not jump then resolve the necessary value instead
    __ee__ load(dx, Value::Boolean(true)), __cc__ bind(bail);
}
