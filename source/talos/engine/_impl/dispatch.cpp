/// Talos Modules
#include "talos/engine/dispatch.hpp"
#include "talos/async/service.hpp"
#include "talos/resource/frame.hpp"

/// Dispatch Modules
#include "talos/engine/_inline/execute.ipp"

//  PUBLIC METHODS  //

Talos::Pointer::Underlying Talos::Engine::Dispatch::getter(
    Runtime::Isolate* isolate, Pointer::Underlying target, Pointer::Underlying symbol) {
    return m_getter(isolate, Value::Any(target), Value::Cast<Value::Symbol>(symbol)).pointer();
}

Talos::Pointer::Underlying Talos::Engine::Dispatch::setter(
    Runtime::Isolate* isolate, Pointer::Underlying target, Pointer::Underlying value, Pointer::Underlying symbol) {
    return m_setter(isolate, Value::Any(target), Value::Any(value), Value::Cast<Value::Symbol>(symbol)).pointer();
}

Talos::Engine::Subtype Talos::Engine::Dispatch::extends(Pointer::Underlying value, Pointer::Underlying guard) {
    return m_extends(Value::Any(value), Value::Any(guard));
}

Talos::Pointer::Underlying Talos::Engine::Dispatch::ensure(
    Isolate* isolate, Pointer::Underlying value, Pointer::Underlying guard) {
    return m_ensure(isolate, Value::Any(value), Value::Any(guard)).pointer();
}

Talos::Pointer::Underlying Talos::Engine::Dispatch::concat(
    Isolate* isolate, Pointer::Underlying left, Pointer::Underlying right) {
    return m_concat(isolate, Value::Any(left), Value::Any(right)).pointer();
}

Talos::Pointer::Underlying Talos::Engine::Dispatch::list(Isolate* isolate, const Function::Arguments& args) {
    return m_list(isolate, args.span()).pointer();
}

Talos::Pointer::Underlying Talos::Engine::Dispatch::object(Isolate* isolate, const Function::Arguments& args) {
    return m_object(isolate, args.span()).pointer();
}

Talos::Pointer::Underlying Talos::Engine::Dispatch::iterator(Isolate* isolate, Pointer::Underlying iterable) {
    return m_iterator(isolate, Value::Any(iterable)).pointer();
}

Talos::Pointer::Underlying Talos::Engine::Dispatch::enumeration(Isolate* isolate, const Function::Arguments& args) {
    return m_enumeration(isolate, args.span()).pointer();
}

//  PRIVATE METHODS  //

Talos::Value::Any Talos::Engine::Dispatch::m_getter(
    Runtime::Isolate* isolate, Function::Frame* frame, Value::Any target, Bytecode::Index index) {
    return m_getter(isolate, target, frame->constant<Value::Symbol>(index));
}

Talos::Value::Any Talos::Engine::Dispatch::m_getter(
    Runtime::Isolate* isolate, Value::Any target, Value::Symbol symbol) {
    auto descriptor = target.attribute(symbol);  // and the descriptor to be used
    auto field = descriptor ? descriptor->getter(isolate, target) : Value::Missing();
    Feedback feedback = { .target = target, .field = field, .symbol = symbol };
    return m_feedback(isolate, feedback), field;  // resolve the feedback now
}

Talos::Value::Any Talos::Engine::Dispatch::m_setter(
    Runtime::Isolate* isolate, Function::Frame* frame, Value::Any target, Value::Any value, Bytecode::Index index) {
    return m_setter(isolate, target, value, frame->constant<Value::Symbol>(index));
}

Talos::Value::Any Talos::Engine::Dispatch::m_setter(
    Runtime::Isolate* isolate, Value::Any target, Value::Any value, Value::Symbol symbol) {
    auto descriptor = target.attribute(symbol);  // and the descriptor to be used
    auto field = descriptor ? descriptor->setter(isolate, target, value) : Value::Missing();
    Feedback feedback = { .target = target, .field = field, .symbol = symbol };
    return m_feedback(isolate, feedback), field;  // resolve the feedback now
}

void Talos::Engine::Dispatch::m_feedback(Isolate* isolate, const Feedback& feedback) {
    // validate the incoming target
    if (!feedback.target.traits().okay()) return;

    // resolve a suitable feedback code to be used
    static $::Map<Value::Feedback, Diagnostic::Code> s_codes = {
        { Value::Feedback::FIELD_MISSING, 6000300 },
        { Value::Feedback::FIELD_IMMUTABLE, 6000301 },
    };

    // fail immediately when feedback does not exist
    auto reference = feedback.field.traits().feedback();
    if (!s_codes.contains(reference)) return;

    // get the necessary details to be shown
    auto type_name = feedback.target.type_name();
    auto* intern = isolate->intern(feedback.symbol);

    // build the necessary panic to be returned
    if (intern) isolate->panic(s_codes.at(reference), type_name, intern->view());
    else isolate->panic(s_codes.at(reference), type_name, feedback.symbol);
}

Talos::Value::Any Talos::Engine::Dispatch::m_execute(Isolate* isolate, Function::Frame* frame) {
    // ensure the frames currently match
    $_ASSERT(isolate->frame() == frame, "Mismatched VM frames");

    // prepare the available dispatch table
    static constexpr void* s_table[] = {
#define TALOS_XX_SYLLABLE_BASE(N, ...) &&_HANDLE_##N,
#include "talos/bytecode/_defines/syllables.def"

#define TALOS_XX_SYLLABLE_BASE(N, ...) &&_DEBUG_##N,
#include "talos/bytecode/_defines/syllables.def"
    };

    // prepare a getter for the next instruction value
    static constexpr auto advance = [](auto& offset, auto& instruction) $_INLINE_ALWAYS -> void* {
        instruction = std::bit_cast<Bytecode::Instruction*>(offset);
        auto syllable = static_cast<size_t>(instruction->syllable());
        return offset += sizeof(Bytecode::Instruction), s_table[syllable];
    };

    // prepare the offset for the current instruction
    auto& offset = frame->offset();

    // prepare the instruction to be handled now
    Bytecode::Instruction* instruction = nullptr;

    // and force an advancement to occur initially
    goto* advance(offset, instruction);

    // prepare the all the dispatch handlers now to be completed
#define TALOS_XX_SYLLABLE_BASE(N, ...)                                                                          \
    _HANDLE_##N : {                                                                                             \
        switch (m_execute<Bytecode::Syllable::N>(isolate, frame, instruction->cast<Bytecode::Syllable::N>())) { \
            case Mode::NEXT: goto* advance(offset, instruction);                                                \
            case Mode::PANIC: goto _RESOLVE_FAILURE;                                                            \
            case Mode::RETURN: goto _RESOLVE_SUCCESS;                                                           \
            case Mode::INTERRUPT: goto _RESOLVE_INTERRUPT;                                                      \
        }                                                                                                       \
    }
#include "talos/bytecode/_defines/syllables.def"

// prepare all the debug handlers now to be completed
#define TALOS_XX_SYLLABLE_BASE(N, ...) \
    _DEBUG_##N : { $_ABORT("Unimplemented"); }

#include "talos/bytecode/_defines/syllables.def"

    // clang-format off
    _RESOLVE_SUCCESS: return frame->accumulator();
    _RESOLVE_FAILURE: return Value::Failure();
    _RESOLVE_INTERRUPT: return isolate->panic(9000200);
    // clang-format on
}
