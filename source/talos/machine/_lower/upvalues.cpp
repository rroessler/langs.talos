/// Inline Modules
#include "talos/machine/_inline/macros.ipp"

/// Forward Declarations
$_FWD(Talos::Machine::Dispatch, Reference lctx(Reference, uint16_t))
$_FWD(Talos::Machine::Dispatch, void sctx(Reference, Reference, uint16_t))
$_FWD(Talos::Machine::Dispatch, Reference lupv(Reference, uint16_t, uint16_t))
$_FWD(Talos::Machine::Dispatch, void supv(Reference, Reference, uint16_t, uint16_t))
$_FWD(Talos::Machine::Template, void load(Builder*, const Engine::Register&, const Engine::Register&, uint16_t))
$_FWD(Talos::Machine::Template, void store(Builder*, const Engine::Register&, const Engine::Register&, uint16_t))

//  PUBLIC METHODS  //

Talos::Machine::Reference Talos::Machine::Dispatch::lctx(Reference context, uint16_t slot) {
    return reinterpret_cast<Function::Context*>(&context)->load(slot).pointer();
}

void Talos::Machine::Dispatch::sctx(Reference context, Reference value, uint16_t slot) {
    reinterpret_cast<Function::Context*>(&context)->store(slot, Value::Any(value));
}

Talos::Machine::Reference Talos::Machine::Dispatch::lupv(Reference context, uint16_t slot, uint16_t depth) {
    return reinterpret_cast<Function::Context*>(&context)->resolve(depth).load(slot).pointer();
}

void Talos::Machine::Dispatch::supv(Reference context, Reference value, uint16_t slot, uint16_t depth) {
    reinterpret_cast<Function::Context*>(&context)->resolve(depth).store(slot, Value::Any(value));
}

void Talos::Machine::Template::load(
    Builder* builder, const Engine::Register& dv, const Engine::Register& slot, uint16_t depth = 0) {
    // prepare the runtime registers
    auto dx = __ee__ resolve(dv);

    // attempt invoking the load context handler
    if (!depth) __ee__ invoke(Dispatch::lctx, dx, builder->envp, slot.encode());
    else __ee__ invoke(Dispatch::lupv, dx, builder->envp, slot.encode(), depth);
}

void Talos::Machine::Template::store(
    Builder* builder, const Engine::Register& tv, const Engine::Register& slot, uint16_t depth = 0) {
    // prepare the runtime registers
    auto tx = __ee__ resolve(tv);

    // attempt invoking the load context handler
    if (!depth) __ee__ invoke(Dispatch::sctx, builder->envp, tx, slot.encode());
    else __ee__ invoke(Dispatch::supv, builder->envp, tx, slot.encode(), depth);
}

//  PRIVATE METHODS  //

TALOS_MM_MACHINE_EMIT(LOAD_CONTEXT, builder, instruction) {
    __tm__ load(builder, instruction->get<0>(), instruction->get<1>());
}

TALOS_MM_MACHINE_EMIT(STORE_CONTEXT, builder, instruction) {
    __tm__ store(builder, instruction->get<0>(), instruction->get<1>());
}

TALOS_MM_MACHINE_EMIT(LOAD_UPVALUE, builder, instruction) {
    __tm__ load(builder, instruction->get<0>(), instruction->get<1>(), instruction->get<2>());
}

TALOS_MM_MACHINE_EMIT(STORE_UPVALUE, builder, instruction) {
    __tm__ store(builder, instruction->get<0>(), instruction->get<1>(), instruction->get<2>());
}
