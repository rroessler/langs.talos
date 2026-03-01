/// Forge Modules
#include "forge/engine/dispatch.hpp"
#include "forge/object/enum.hpp"
#include "forge/runtime/isolate.hpp"

/// Inline Modules
#include "forge/machine/_inline/macros.ipp"

/// Forward Declarations
$_FWD(static Reference empty(Runtime::Isolate*), Forge::Machine::Dispatch)
$_FWD(Reference enumeration(Runtime::Isolate*, Value::Any*), Forge::Machine::Dispatch)

//  PUBLIC METHODS  //

Forge::Machine::Reference Forge::Machine::Dispatch::empty(Runtime::Isolate* isolate) {
    return isolate->create<Object::Enum>().pointer();  // ensure faster
}

Forge::Machine::Reference Forge::Machine::Dispatch::enumeration(Runtime::Isolate* isolate, Value::Any* span) {
    return Engine::Dispatch::enumeration(isolate, Template::arguments(span));
}

//  PRIVATE METHODS  //

FORGE_MM_MACHINE_EMIT(ENUM_EMPTY, builder, instruction) {
    auto dx = __ee__ resolve(instruction->get<0>());
    __ee__ invoke(Dispatch::empty, dx, builder->isolate);
}

FORGE_MM_MACHINE_EMIT(ENUM_MAKE, builder, instruction) {
    // prepare the necessary registers to be used
    auto dx = __ee__ resolve(instruction->get<0>());

    // ensure we preload the necessary parameters
    __ee__ parameters(instruction->get<1>());

    // and invoke the incoming enumeration details
    __ee__ invoke(Dispatch::enumeration, dx, builder->isolate, builder->stack);
}
