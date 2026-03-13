/// Talos Modules
#include "talos/engine/dispatch.hpp"
#include "talos/object/instance.hpp"
#include "talos/runtime/isolate.hpp"

/// Inline Modules
#include "talos/machine/_inline/macros.ipp"

/// Forward Declarations
$_FWD(Talos::Machine::Dispatch, static Reference empty(Runtime::Isolate*))
$_FWD(Talos::Machine::Dispatch, Reference object(Runtime::Isolate*, Value::Any*))

//  PUBLIC METHODS  //

Talos::Machine::Reference Talos::Machine::Dispatch::empty(Runtime::Isolate* isolate) {
    return isolate->create<Object::Instance>().pointer();
}

Talos::Machine::Reference Talos::Machine::Dispatch::object(Runtime::Isolate* isolate, Value::Any* span) {
    return Engine::Dispatch::object(isolate, Template::arguments(span));
}

//  PRIVATE METHODS  //

TALOS_MM_MACHINE_EMIT(OBJECT_EMPTY, builder, instruction) {
    auto dx = __ee__ resolve(instruction->get<0>());
    __ee__ invoke(Dispatch::empty, dx, builder->isolate);
}

TALOS_MM_MACHINE_EMIT(OBJECT_MAKE, builder, instruction) {
    // prepare the necessary registers to be used
    auto dx = __ee__ resolve(instruction->get<0>());

    // ensure we preload the necessary parameters
    __ee__ parameters(instruction->get<1>());

    // and invoke the incoming object constructor
    __ee__ invoke(Dispatch::object, dx, builder->isolate, builder->stack);
}

TALOS_MM_MACHINE_UNIMPLEMENTED(OBJECT_ATTR, , )
