/// Talos Modules
#include "talos/engine/frame.hpp"
#include "talos/runtime/isolate.hpp"
#include "talos/string/small.hpp"
#include "talos/value/boolean.hpp"

/// Inline Modules
#include "talos/machine/_inline/macros.ipp"

/// Forward Declarations
$_FWD(void interrupted(Builder*), Talos::Machine::Template)
$_FWD(uint64_t interrupted(Runtime::Isolate*), Talos::Machine::Dispatch)

//  PUBLIC METHODS  //

uint64_t Talos::Machine::Dispatch::interrupted(Runtime::Isolate* isolate) {
    auto* frame = isolate->frame();  // get frame
    return $_ASSERT(frame), frame->interrupted();
}

void Talos::Machine::Template::interrupted(Builder* builder) {
    // prepare a boolean result register
    auto dx = __cc__ new_gp64("@dx");

    // attempt calling the interrupted state getter
    __ee__ invoke(Dispatch::interrupted, dx, builder->isolate);

    // if the flag has been set, then we force a panic to occur
    __ee__ interrupt(dx);
}

//  PRIVATE METHODS  //

TALOS_MM_MACHINE_EMIT(JUMP_TO, builder, instruction) {
    // attempt resolving the incoming label
    auto lv = instruction->get<0>();

    // pre-check if the interrupt flag is set at all
    __tm__ interrupted(builder);

    // jump to the incoming label as needed
    __cc__ j(__ee__ label(lv));
}

TALOS_MM_MACHINE_EMIT(JUMP_FILLED, builder, instruction) {
    // attempt resolving the incoming label
    auto label = __ee__ label(instruction->get<0>());

    // resolve the necessary incoming register
    auto tv = instruction->get<1>();
    auto tx = __cc__ new_gp64("@tx");

    // prepare the incoming test value now
    auto empty = __iv__(Value::Void());

    // pre-check if the interrupt flag has been set at all
    __tm__ interrupted(builder);

    // attempt testing against the filled condition now
    __ee__ move(tx, tv), __cc__ j(label, asmjit::ujit::cmp_ne(tx, empty));
}

TALOS_MM_MACHINE_EMIT(JUMP_TRUTHY, builder, instruction) {
    // resolve the necessary incoming register
    auto tv = instruction->get<1>();

    // attempt resolving the incoming label
    auto label = __ee__ label(instruction->get<0>());

    // pre-check if the interrupt flag has been set at all
    __tm__ interrupted(builder);

    // jump when the incoming value is truthy at all
    __ee__ truthy(label, tv);
}

TALOS_MM_MACHINE_EMIT(JUMP_FALSEY, builder, instruction) {
    // resolve the necessary incoming register
    auto tv = instruction->get<1>();

    // attempt resolving the incoming label
    auto label = __ee__ label(instruction->get<0>());

    // pre-check if the interrupt flag has been set at all
    __tm__ interrupted(builder);

    // jump when the incoming value is falsey
    __ee__ falsey(label, tv);
}
