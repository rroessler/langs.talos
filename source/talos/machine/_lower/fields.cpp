/// Talos Modules
#include "talos/engine/dispatch.hpp"

/// Inline Modules
#include "talos/machine/_inline/macros.ipp"

//  PRIVATE METHODS  //

TALOS_MM_MACHINE_EMIT(LOAD_FIELD, builder, instruction) {
    // prepare the underlying fields
    auto dv = instruction->get<0>();
    auto tv = instruction->get<1>();
    auto index = instruction->get<2>();

    // request the field getter template now
    __tm__ getter(builder, dv, tv, index);
}

TALOS_MM_MACHINE_EMIT(STORE_FIELD, builder, instruction) {
    // prepare the underlying fields
    auto tv = instruction->get<0>();
    auto sv = instruction->get<1>();
    auto index = instruction->get<2>();

    // prepare the registers to be used now
    auto tx = __ee__ resolve(tv);
    auto sx = __ee__ resolve(sv);
    auto cx = __cc__ new_gp64("@cx");

    // attempt loading the constant to be used
    __ee__ load(cx, builder->info->arena()->constants[index]);
    __ee__ invoke(Engine::Dispatch::setter, cx, builder->isolate, tx, sx, cx);

    // finally post-validate the result was not a failure
    __ee__ validate(cx, Validate::SLOW);
}
