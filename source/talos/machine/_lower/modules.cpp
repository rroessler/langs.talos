/// Talos Modules
#include "talos/engine/dispatch.hpp"
#include "talos/engine/exports.hpp"
#include "talos/machine/frame.hpp"
#include "talos/object/instance.hpp"
#include "talos/runtime/isolate.hpp"

/// Inline Modules
#include "talos/machine/_inline/macros.ipp"

/// Forward Declarations
$_FWD(Talos::Machine::Dispatch, Reference open(Runtime::Isolate*))
$_FWD(Talos::Machine::Dispatch, Reference close(Runtime::Isolate*))
$_FWD(Talos::Machine::Dispatch, Reference import(Runtime::Isolate*, const String::Intern*))

//  PUBLIC METHODS  //

Talos::Machine::Reference Talos::Machine::Dispatch::open(Runtime::Isolate* isolate) {
    const auto* frame = isolate->frame()->as<Machine::Frame>();
    return isolate->exports(frame->resource())->open(isolate).pointer();
}

Talos::Machine::Reference Talos::Machine::Dispatch::close(Runtime::Isolate* isolate) {
    const auto* frame = isolate->frame()->as<Machine::Frame>();
    return isolate->exports(frame->resource())->close().pointer();
}

Talos::Machine::Reference Talos::Machine::Dispatch::import(Runtime::Isolate* isolate, const String::Intern* intern) {
    const auto* frame = isolate->frame()->as<Machine::Frame>();  // get the base frame
    auto trace = frame->backtrace(Resource::Group::IMPORT);      // prepare the trace now
    return isolate->import(intern->view(), frame->resource().body(), trace).pointer();
}

//  PRIVATE METHODS  //

TALOS_MM_MACHINE_EMIT(MODULE_OPEN, builder, instruction) {
    auto dx = __ee__ resolve(instruction->get<0>());
    __ee__ invoke(Dispatch::open, dx, builder->isolate);
}

TALOS_MM_MACHINE_EMIT(MODULE_CLOSE, builder, instruction) {
    auto dx = __ee__ resolve(instruction->get<0>());
    __ee__ invoke(Dispatch::close, dx, builder->isolate);
}

TALOS_MM_MACHINE_UNIMPLEMENTED(MODULE_BARREL, , )

TALOS_MM_MACHINE_EMIT(MODULE_IMPORT, builder, instruction) {
    // prepare the necessary arguments
    auto dx = __ee__ resolve(instruction->get<0>());
    auto ix = __ee__ intern(instruction->get<1>());

    // attempt importing into the required slot
    __ee__ invoke(Dispatch::import, dx, builder->isolate, ix);

    // validate the outgoing result
    __ee__ validate(dx, Validate::FAST);
}

TALOS_MM_MACHINE_EMIT(MODULE_EXPORT, builder, instruction) {
    // prepare a suitable output register
    auto dx = __cc__ new_gp64("@dx");

    // prepare the necessary arguments
    auto sx = __ee__ resolve(instruction->get<0>());
    auto ix = __ee__ intern(instruction->get<1>());

    // attempt exporting the value now
    __ee__ invoke(Engine::Dispatch::expose, dx, builder->isolate, sx, ix);

    // validate the outgoing result
    __ee__ validate(dx, Validate::FAST);
}
