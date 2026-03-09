/// Talos Modules
#include "talos/globals/service.hpp"
#include "talos/machine/frame.hpp"
#include "talos/runtime/isolate.hpp"

/// Inline Modules
#include "talos/machine/_inline/macros.ipp"
#include "talos/value/_inline/value.ipp"

/// Forward Declarations
$_FWD(Talos::Machine::Dispatch, Reference self(Runtime::Isolate*))
$_FWD(Talos::Machine::Dispatch, Reference global(Runtime::Isolate*, Reference))

//  PROPERTIES  //

static constexpr auto g_void = Talos::Value::Void();
static constexpr auto g_one = Talos::Number::Tagged(1);
static constexpr auto g_zero = Talos::Number::Tagged(0);
static constexpr auto g_true = Talos::Value::Boolean(true);
static constexpr auto g_false = Talos::Value::Boolean(false);

//  PUBLIC METHODS  //

Talos::Machine::Reference Talos::Machine::Dispatch::global(Runtime::Isolate* isolate, Reference symbol) {
    return isolate->global(Value::Cast<Value::Symbol>(symbol)).pointer();
}

Talos::Machine::Reference Talos::Machine::Dispatch::self(Runtime::Isolate* isolate) {
    return isolate->frame()->as<Machine::Frame>()->self().pointer();
}

//  PRIVATE METHODS  //

TALOS_MM_MACHINE_EMIT(LOAD_ZERO, builder, instruction) { __ee__ load(instruction->get<0>(), g_zero); }
TALOS_MM_MACHINE_EMIT(LOAD_ONE, builder, instruction) { __ee__ load(instruction->get<0>(), g_one); }
TALOS_MM_MACHINE_EMIT(LOAD_VOID, builder, instruction) { __ee__ load(instruction->get<0>(), g_void); }
TALOS_MM_MACHINE_EMIT(LOAD_TRUE, builder, instruction) { __ee__ load(instruction->get<0>(), g_true); }
TALOS_MM_MACHINE_EMIT(LOAD_FALSE, builder, instruction) { __ee__ load(instruction->get<0>(), g_false); }

TALOS_MM_MACHINE_EMIT(LOAD_SELF, builder, instruction) {
    auto dx = __ee__ resolve(instruction->get<0>());
    __ee__ invoke(Dispatch::self, dx, builder->isolate);
}

TALOS_MM_MACHINE_EMIT(LOAD_CONST, builder, instruction) {
    // prepare our incoming details
    auto index = instruction->get<1>();
    auto* arena = builder->info->arena();
    auto constant = arena->constants[index];

    // and emit the load request now
    __ee__ load(instruction->get<0>(), constant);
}

TALOS_MM_MACHINE_EMIT(LOAD_GLOBAL, builder, instruction) {
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
