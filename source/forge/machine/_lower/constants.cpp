/// Forge Modules
#include "forge/globals/service.hpp"
#include "forge/runtime/isolate.hpp"

/// Inline Modules
#include "forge/machine/_inline/macros.ipp"
#include "forge/value/_inline/value.ipp"

/// Forward Declarations
$_FWD(Reference global(Runtime::Isolate*, Reference), Forge::Machine::Dispatch)

//  PROPERTIES  //

static constexpr auto g_void = Forge::Value::Void();
static constexpr auto g_one = Forge::Number::Tagged(1);
static constexpr auto g_zero = Forge::Number::Tagged(0);
static constexpr auto g_true = Forge::Value::Boolean(true);
static constexpr auto g_false = Forge::Value::Boolean(false);

//  PUBLIC METHODS  //

Forge::Machine::Reference Forge::Machine::Dispatch::global(Runtime::Isolate* isolate, Reference symbol) {
    return isolate->global(Value::Cast<Value::Symbol>(symbol)).pointer();
}

//  PRIVATE METHODS  //

FORGE_MM_MACHINE_EMIT(LOAD_ZERO, builder, instruction) { __ee__ load(instruction->get<0>(), g_zero); }
FORGE_MM_MACHINE_EMIT(LOAD_ONE, builder, instruction) { __ee__ load(instruction->get<0>(), g_one); }
FORGE_MM_MACHINE_EMIT(LOAD_VOID, builder, instruction) { __ee__ load(instruction->get<0>(), g_void); }
FORGE_MM_MACHINE_EMIT(LOAD_TRUE, builder, instruction) { __ee__ load(instruction->get<0>(), g_true); }
FORGE_MM_MACHINE_EMIT(LOAD_FALSE, builder, instruction) { __ee__ load(instruction->get<0>(), g_false); }

FORGE_MM_MACHINE_EMIT(LOAD_CONST, builder, instruction) {
    // prepare our incoming details
    auto index = instruction->get<1>();
    auto* arena = builder->info->arena();
    auto constant = arena->constants[index];

    // and emit the load request now
    __ee__ load(instruction->get<0>(), constant);
}

FORGE_MM_MACHINE_EMIT(LOAD_GLOBAL, builder, instruction) {
    // prepare some incoming details
    auto dv = instruction->get<0>();
    auto index = instruction->get<1>();
    auto* arena = builder->info->arena();
    auto constant = arena->constants[index];

    // prepare a register to return the global
    auto dx = __ee__ resolve(dv);

    // load the incoming constant to be used
    __ee__ load(dx, constant);

    // attempt getting the necessary global now
    __ee__ invoke(Dispatch::global, dx, builder->isolate, dx);
}
