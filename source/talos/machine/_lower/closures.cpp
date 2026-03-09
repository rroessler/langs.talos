/// Talos Modules
#include "talos/engine/dispatch.hpp"
#include "talos/machine/frame.hpp"
#include "talos/runtime/isolate.hpp"

/// Inline Modules
#include "talos/machine/_inline/macros.ipp"

/// Forward Declarations
$_FWD(Talos::Machine::Dispatch, Reference passthrough(Runtime::Isolate*))
$_FWD(Talos::Machine::Dispatch, Reference closure(Runtime::Isolate*, const Function::Info*))

//  PUBLIC METHODS  //

Talos::Machine::Reference Talos::Machine::Dispatch::passthrough(Runtime::Isolate* isolate) {
    // get the underlying frame instance to be used
    const auto* frame = isolate->frame()->as<Machine::Frame>();

    // get the context to be destructured
    auto* args = frame->argv();
    auto context = frame->context();

    // ensure that are context and arguments are matched
    $_ASSERT(args->self() == frame->self());

    // should safely be able to invoke the call
    return Engine::Call::any(isolate, context.load(0), *args).pointer();
}

Talos::Machine::Reference Talos::Machine::Dispatch::closure(Runtime::Isolate* isolate, const Function::Info* info) {
    const auto* frame = isolate->frame()->as<Machine::Frame>();  // get frame to be used now
    return isolate->create<Function::Closure>(info, frame->self(), frame->context()).pointer();
}

//  PRIVATE METHODS  //

TALOS_MM_MACHINE_EMIT(CLOSURE_MAKE, builder, instruction) {
    // prepare the function information to be encoded
    auto index = instruction->get<1>();
    auto* arena = builder->info->arena();
    auto* info = arena->functions.at(index).get();

    // prepare a destination register to be used now
    auto dv = instruction->get<0>();
    auto dx = __cc__ new_gpz("@dx");

    // move the initial function information here
    __cc__ mov(dx, info);

    // request constructing the outgoing details now
    __ee__ invoke(Dispatch::closure, dx, builder->isolate, dx);

    // finally emplace the result in the destination
    __ee__ move(dv, dx);
}

TALOS_MM_MACHINE_EMIT(CLOSURE_PASS, builder, instruction) {
    // prepare the necessary registers
    auto dx = __ee__ resolve(instruction->get<0>());

    // then we want to attempt an invocation now
    __ee__ invoke(Dispatch::passthrough, dx, builder->isolate);

    // validate the outgoing result is alright
    __ee__ validate(dx, Validate::FAST);
}

TALOS_MM_MACHINE_EMIT(CALL_0_VOID, builder, instruction) {
    // prepare the incoming registers
    auto dv = instruction->get<0>();

    // and attempt compiling the invocation now
    __tm__ invoke(builder, dv, Engine::Accumulator());
}

TALOS_MM_MACHINE_EMIT(CALL_N_VOID, builder, instruction) {
    // prepare the incoming registers
    auto dv = instruction->get<0>();

    // prepare the necessary arguments span
    auto span = instruction->get<1>();

    // and attempt compiling the invocation now
    __tm__ invoke(builder, dv, span.first(), span.slice(1));
}

TALOS_MM_MACHINE_EMIT(CALL_0_INLINE, builder, instruction) { __tm__ recall(builder, instruction->get<0>()); }
TALOS_MM_MACHINE_EMIT(CALL_N_INLINE, builder, instruction) {
    __tm__ recall(builder, instruction->get<0>(), instruction->get<1>());
}

TALOS_MM_MACHINE_EMIT(CALL_0_FIELD, builder, instruction) {
    // prepare the incoming registers
    auto dv = instruction->get<0>();
    auto index = instruction->get<1>();
    auto target = Engine::Accumulator();

    // attempt getting the callee value
    auto cx = __tm__ getter(builder, target, index);

    // since a success, attempt the necessary invocation now
    __tm__ invoke(builder, dv, cx, target);
}

TALOS_MM_MACHINE_EMIT(CALL_N_FIELD, builder, instruction) {
    // prepare the incoming registers
    auto dv = instruction->get<0>();
    auto index = instruction->get<1>();
    auto span = instruction->get<2>();
    auto target = span.first();

    // attempt getting the callee value
    auto cx = __tm__ getter(builder, target, index);

    // since a success, attempt the necessary invocation now
    __tm__ invoke(builder, dv, cx, target, span.slice(1));
}

TALOS_MM_MACHINE_EMIT(SPAWN_0_VOID, builder, instruction) {
    // prepare the incoming registers
    auto dv = instruction->get<0>();

    // and attempt compiling the invocation now
    __tm__ spawn(builder, dv, Engine::Accumulator());
}

TALOS_MM_MACHINE_EMIT(SPAWN_N_VOID, builder, instruction) {
    // prepare the incoming registers
    auto dv = instruction->get<0>();

    // prepare the necessary arguments span
    auto span = instruction->get<1>();

    // and attempt compiling the invocation now
    __tm__ spawn(builder, dv, span.first(), span.slice(1));
}

TALOS_MM_MACHINE_EMIT(SPAWN_0_FIELD, builder, instruction) {
    // prepare the incoming registers
    auto dv = instruction->get<0>();
    auto index = instruction->get<1>();
    auto target = Engine::Accumulator();

    // attempt getting the callee value
    auto cx = __tm__ getter(builder, target, index);

    // since a success, attempt the necessary invocation now
    __tm__ spawn(builder, dv, cx, target);
}

TALOS_MM_MACHINE_EMIT(SPAWN_N_FIELD, builder, instruction) {
    // prepare the incoming registers
    auto dv = instruction->get<0>();
    auto index = instruction->get<1>();
    auto span = instruction->get<2>();
    auto target = span.first();

    // attempt getting the callee value
    auto cx = __tm__ getter(builder, target, index);

    // since a success, attempt the necessary invocation now
    __tm__ spawn(builder, dv, cx, target, span.slice(1));
}