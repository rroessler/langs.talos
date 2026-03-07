/// Talos Modules
#include "talos/globals/service.hpp"

/// Inline Modules
#include "talos/engine/_inline/macros.ipp"
#include "talos/value/_inline/value.ipp"

//  PROPERTIES  //

static constexpr auto g_void = Talos::Value::Void();
static constexpr auto g_one = Talos::Number::Tagged(1);
static constexpr auto g_zero = Talos::Number::Tagged(0);
static constexpr auto g_true = Talos::Value::Boolean(true);
static constexpr auto g_false = Talos::Value::Boolean(false);

//  PRIVATE METHODS  //

TALOS_MM_ENGINE_EXECUTE(LOAD_ZERO, , frame, ii) { return frame->store(ii->get<0>(), g_zero), Mode::NEXT; }
TALOS_MM_ENGINE_EXECUTE(LOAD_ONE, , frame, ii) { return frame->store(ii->get<0>(), g_one), Mode::NEXT; }
TALOS_MM_ENGINE_EXECUTE(LOAD_VOID, , frame, ii) { return frame->store(ii->get<0>(), g_void), Mode::NEXT; }
TALOS_MM_ENGINE_EXECUTE(LOAD_TRUE, , frame, ii) { return frame->store(ii->get<0>(), g_true), Mode::NEXT; }
TALOS_MM_ENGINE_EXECUTE(LOAD_FALSE, , frame, ii) { return frame->store(ii->get<0>(), g_false), Mode::NEXT; }

TALOS_MM_ENGINE_EXECUTE(LOAD_CONST, , frame, instruction) {
    auto constant = frame->constant(instruction->get<1>());
    return frame->store(instruction->get<0>(), constant), Mode::NEXT;
}

TALOS_MM_ENGINE_EXECUTE(LOAD_GLOBAL, isolate, frame, instruction) {
    auto symbol = frame->constant<Value::Symbol>(instruction->get<1>());
    return frame->store(instruction->get<0>(), isolate->global(symbol)), Mode::NEXT;
}
