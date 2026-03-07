/// Talos Modules
#include "talos/async/future.hpp"
#include "talos/machine/service.hpp"

/// Engine Modules
#include "talos/engine/_inline/macros.ipp"

//  PUBLIC METHODS  //

$_INLINE_FORCE Talos::Engine::Mode Talos::Engine::Dispatch::m_recall(
    Runtime::Isolate* isolate, Function::Frame* frame, Register sink, const Arguments& args) {
    auto result = Call::inlined(isolate, frame, args);
    if (!result.traits().okay()) return Mode::PANIC;
    return frame->store(sink, result), Mode::NEXT;
}

$_INLINE_FORCE Talos::Engine::Mode Talos::Engine::Dispatch::m_invoke(
    Runtime::Isolate* isolate, Function::Frame* frame, Register sink, Value::Any target, const Arguments& args) {
    auto result = Call::any(isolate, target, args);
    if (!result.traits().okay()) return Mode::PANIC;
    return frame->store(sink, result), Mode::NEXT;
}

$_INLINE_FORCE Talos::Engine::Mode Talos::Engine::Dispatch::m_spawn(
    Runtime::Isolate* isolate, Function::Frame* frame, Register sink, Value::Any target, const Arguments& args) {
    // ensure we have a valid dynamic function
    if (!target.is<Function::Dynamic>()) return isolate->panic(6000201, target.type_name()), Mode::PANIC;

    auto callback = target.as<Function::Dynamic>();  // prepare
    auto result = isolate->create<Async::Future>(callback, args);

    // bind the result to the necessary position
    return frame->store(sink, result), Mode::NEXT;
}

//  PRIVATE METHODS  //

TALOS_MM_ENGINE_EXECUTE(CLOSURE_MAKE, isolate, frame, instruction) {
    auto* info = frame->arena()->functions.at(instruction->get<1>()).get();
    auto closure = isolate->create<Function::Closure>(info, frame->context());
    return frame->store(instruction->get<0>(), closure), Mode::NEXT;
}

TALOS_MM_ENGINE_EXECUTE(CLOSURE_PASS, isolate, frame, instruction) {
    // get the associated context
    auto context = frame->context();

    // ensure the incoming context is valid
    $_ASSERT(context.valid());

    // prepare the self and callee values
    auto self = context.self(), callee = context.load(0);

    // construct the necessary arguments now
    Arguments args = { self, frame->argv() };

    // attempt calling the instance
    return m_invoke(isolate, frame, instruction->get<0>(), callee, args);
}

TALOS_MM_ENGINE_EXECUTE(CALL_0_VOID, isolate, frame, instruction) {
    return m_invoke(isolate, frame, instruction->get<0>(), frame->accumulator());
}

TALOS_MM_ENGINE_EXECUTE(CALL_N_VOID, isolate, frame, instruction) {
    auto [callee, argv] = frame->split(instruction->get<1>());
    return m_invoke(isolate, frame, instruction->get<0>(), callee, argv);
}

TALOS_MM_ENGINE_EXECUTE(CALL_0_INLINE, isolate, frame, instruction) {
    return m_recall(isolate, frame, instruction->get<0>());
}

TALOS_MM_ENGINE_EXECUTE(CALL_N_INLINE, isolate, frame, instruction) {
    return m_recall(isolate, frame, instruction->get<0>(), frame->span(instruction->get<1>()));
}

TALOS_MM_ENGINE_EXECUTE(CALL_0_FIELD, isolate, frame, instruction) {
    auto target = frame->accumulator();  // get the baseline target
    auto callee = m_getter(isolate, frame, target, instruction->get<1>());
    if (!callee.traits().okay()) return Mode::PANIC;  // fail early if possible
    return m_invoke(isolate, frame, instruction->get<0>(), callee, { target });
}

TALOS_MM_ENGINE_EXECUTE(CALL_N_FIELD, isolate, frame, instruction) {
    auto [target, argv] = frame->split(instruction->get<2>());
    auto callee = m_getter(isolate, frame, target, instruction->get<1>());
    if (!callee.traits().okay()) return Mode::PANIC;  // failed calling so exit now
    return m_invoke(isolate, frame, instruction->get<0>(), callee, { target, argv });
}

TALOS_MM_ENGINE_EXECUTE(SPAWN_0_VOID, isolate, frame, instruction) {
    return m_spawn(isolate, frame, instruction->get<0>(), frame->accumulator());
}

TALOS_MM_ENGINE_EXECUTE(SPAWN_N_VOID, isolate, frame, instruction) {
    auto [callee, argv] = frame->split(instruction->get<1>());
    return m_spawn(isolate, frame, instruction->get<0>(), callee, argv);
}

TALOS_MM_ENGINE_EXECUTE(SPAWN_0_FIELD, isolate, frame, instruction) {
    auto target = frame->accumulator();  // get the baseline target
    auto callee = m_getter(isolate, frame, target, instruction->get<1>());
    if (!callee.traits().okay()) return Mode::PANIC;  // fail early if possible
    return m_spawn(isolate, frame, instruction->get<0>(), callee, { target });
}

TALOS_MM_ENGINE_EXECUTE(SPAWN_N_FIELD, isolate, frame, instruction) {
    auto [target, argv] = frame->split(instruction->get<2>());
    auto callee = m_getter(isolate, frame, target, instruction->get<1>());
    if (!callee.traits().okay()) return Mode::PANIC;  // failed calling so exit now
    return m_spawn(isolate, frame, instruction->get<0>(), callee, { target, argv });
}
