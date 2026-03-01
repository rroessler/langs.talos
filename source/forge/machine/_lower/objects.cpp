/// Forge Modules
#include "forge/engine/dispatch.hpp"
#include "forge/object/instance.hpp"
#include "forge/runtime/isolate.hpp"

/// Inline Modules
#include "forge/machine/_inline/macros.ipp"

/// Forward Declarations
$_FWD(static Reference empty(Runtime::Isolate*), Forge::Machine::Dispatch)
$_FWD(Reference object(Runtime::Isolate*, Value::Any*), Forge::Machine::Dispatch)

//  PUBLIC METHODS  //

Forge::Machine::Reference Forge::Machine::Dispatch::empty(Runtime::Isolate* isolate) {
    return isolate->create<Object::Instance>().pointer();
}

Forge::Machine::Reference Forge::Machine::Dispatch::object(Runtime::Isolate* isolate, Value::Any* span) {
    return Engine::Dispatch::object(isolate, Template::arguments(span));
}

//  PRIVATE METHODS  //

FORGE_MM_MACHINE_EMIT(OBJECT_EMPTY, builder, instruction) {
    auto dx = __ee__ resolve(instruction->get<0>());
    __ee__ invoke(Dispatch::empty, dx, builder->isolate);
}

FORGE_MM_MACHINE_EMIT(OBJECT_MAKE, builder, instruction) {
    // prepare the necessary registers to be used
    auto dx = __ee__ resolve(instruction->get<0>());

    // ensure we preload the necessary parameters
    __ee__ parameters(instruction->get<1>());

    // and invoke the incoming object constructor
    __ee__ invoke(Dispatch::object, dx, builder->isolate, builder->stack);
}
