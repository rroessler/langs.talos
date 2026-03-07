/// Talos Modules
#include "talos/engine/exports.hpp"
#include "talos/machine/frame.hpp"
#include "talos/object/instance.hpp"
#include "talos/runtime/isolate.hpp"

/// Inline Modules
#include "talos/machine/_inline/macros.ipp"

/// Forward Declarations
$_FWD(Reference open(Runtime::Isolate*), Talos::Machine::Dispatch)
$_FWD(Reference close(Runtime::Isolate*), Talos::Machine::Dispatch)
$_FWD(Reference import(Runtime::Isolate*, const String::Intern*), Talos::Machine::Dispatch)
$_FWD(Reference expose(Runtime::Isolate*, Reference, const String::Intern*), Talos::Machine::Dispatch)

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

Talos::Machine::Reference Talos::Machine::Dispatch::expose(
    Runtime::Isolate* isolate, Reference value, const String::Intern* intern) {
    // get the current machine frame being used
    const auto* frame = isolate->frame()->as<Machine::Frame>();

    // attempt getting the underlying exports
    auto* exports = isolate->exports(frame->resource());
    if (exports == nullptr) return Value::Failure().pointer();

    // get the underlying fields to be updated now
    auto& fields = exports->current().as<Object::Instance>().fields();
    auto exists = $_UNLIKELY(fields.contains(intern->symbol()));
    if (exists) return isolate->panic(8000301, intern->view()).pointer();

    // construct and emplace the field to be used now
    auto reference = $::New().unique<Member::Reference>(Value::Any(value));
    return fields.emplace(intern->symbol(), std::move(reference)), Value::Void().pointer();
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
    __ee__ invoke(Dispatch::expose, dx, builder->isolate, sx, ix);

    // validate the outgoing result
    __ee__ validate(dx, Validate::FAST);
}
