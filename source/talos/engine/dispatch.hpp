#ifndef _TALOS_ENGINE_DISPATCH_HPP
#define _TALOS_ENGINE_DISPATCH_HPP

/// Talos Modules
#include "talos/function/dynamic.hpp"
#include "talos/function/frame.hpp"
#include "talos/number/tagged.hpp"
#include "talos/runtime/isolate.hpp"
#include "talos/string/dynamic.hpp"

namespace Talos::Engine {

    /// @brief Alias the function arguments.
    using Arguments = Function::Arguments;

    /// @brief Available Dispatching Modes.
    enum class Mode : uint8_t { NEXT, RETURN, PANIC, INTERRUPT };

    /// @brief Inheritance Subtyping Result.
    enum class Subtype : uint8_t { SUCCESS, FAILURE, MISMATCH };

    /// @brief Feedback Analysis Structure.
    struct Feedback {
        Value::Any target = Value::Void();
        Value::Any field = Value::Void();
        Value::Symbol symbol = Value::Symbol();
    };

    /// @brief Interpreter Call Dispatching.
    struct Call : public $::Never {
        //  PUBLIC METHODS  //

        /**
         * @brief Handles calling any suitable value.
         * @param isolate               Runtime isolate.
         * @param target                Target to call.
         * @param args                  Arguments to bind.
         */
        static Value::Any any(Isolate* isolate, Value::Any target, const Arguments& args = {});

        /**
         * @brief Explicit interpreter dispatching.
         * @param isolate               Runtime isolate.
         * @param native                Native to call.
         * @param args                  Arguments to bind.
         */
        static Value::Any native(Isolate* isolate, Function::Native native, const Arguments& args = {});

        /**
         * @brief Explicit interpreter dispatching.
         * @param isolate               Runtime isolate.
         * @param closure               Closure to call.
         * @param args                  Arguments to bind.
         */
        static Value::Any closure(Isolate* isolate, Function::Closure closure, const Arguments& args = {});

        /**
         * @brief Explicit class constructor.
         * @param isolate               Runtime isolate.
         * @param prototype             Class to construct.
         * @param args                  Arguments to bind.
         */
        static Value::Any construct(Isolate* isolate, Object::Class prototype, const Arguments& args = {});

        /**
         * @brief Explicit interpreter dispatching.
         * @param isolate               Runtime isolate.
         * @param frame                 Inlined frame.
         * @param args                  Arguments to bind.
         */
        static Value::Any inlined(Isolate* isolate, Function::Frame* frame, const Arguments& args = {});
        static Value::Any inlined(Isolate* isolate, const Machine::Info* info, const Arguments& args = {});

        /**
         * @brief Explicit interpreter dispatching.
         * @param isolate               Runtime isolate.
         * @param info                  Machine information.
         * @param args                  Arguments to bind.
         */
        static Value::Any jitted(Isolate* isolate, Function::Jitted jitted, const Arguments& args = {});

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles validating any function instance.
         * @param isolate               Runtime isolate.
         */
        static bool m_validate(Isolate* isolate, size_t arity, const Arguments& arguments);
        static bool m_validate(Isolate* isolate, Function::Dynamic target, const Arguments& arguments);
        static bool m_validate(Isolate* isolate, const Function::Info* info, const Arguments& arguments);

        /**
         * @brief Handles defining a context for a closure.
         * @param isolate               Runtime isolate.
         * @param leaked                Total upvalues.
         * @param context               Parent context.
         */
        static Function::Context m_initialize(Isolate* isolate, size_t leaked, Function::Context context);

        /**
         * @brief Handles finalizing results.
         * @param isolate                Runtime isolate.
         * @param result                 Outgoing result.
         */
        static Value::Any m_finalize(Isolate* isolate, Value::Any result);

        /**
         * @brief Explicit interpreter dispatching.
         * @param isolate               Runtime isolate.
         * @param info                  Function info.
         * @param context               Closure context.
         * @param args                  Arguments to bind.
         */
        static Value::Any m_closure(
            Isolate* isolate, const Function::Info* info, Function::Context context, const Arguments& args);

        /**
         * @brief Explicit jitted dispatching.
         * @param isolate               Runtime isolate.
         * @param info                  Machine callee.
         * @param context               Closure context.
         * @param args                  Arguments to bind.
         */
        static Value::Any m_jitted(
            Isolate* isolate, const Machine::Info* info, Function::Context context, const Arguments& args);
    };

    /// @brief Interpreter Dispatching.
    class Dispatch : public $::Never {
        //  TYPEDEFS  //

        /// @brief Allow calls internal access.
        friend struct Call;

       public:
        //  PUBLIC METHODS  //

        /**
         * @brief Handles exposing getters to native code.
         * @param isolate               Runtime isolate.
         * @param target                Getter target.
         * @param symbol                Field symbol.
         */
        static Pointer::Underlying getter(Isolate* isolate, Pointer::Underlying target, Pointer::Underlying symbol);

        /**
         * @brief Handles exposing setters to native code.
         * @param isolate               Runtime isolate.
         * @param target                Setter target.
         * @param value                 Setter value.
         * @param symbol                Field symbol.
         */
        static Pointer::Underlying setter(
            Isolate* isolate, Pointer::Underlying target, Pointer::Underlying value, Pointer::Underlying symbol);

        /**
         * @brief Checks if a value extends a guard.
         * @param value                 Value to check.
         * @param guard                 Incoming guard.
         */
        static Subtype extends(Pointer::Underlying value, Pointer::Underlying guard);
        static Pointer::Underlying ensure(Isolate* isolate, Pointer::Underlying value, Pointer::Underlying guard);

        /**
         * @brief Handles concatenating strings.
         * @param isolate               Runtime isolate.
         * @param left                  Left-hand side.
         * @param right                 Right-hand side.
         */
        static Pointer::Underlying concat(Isolate* isolate, Pointer::Underlying left, Pointer::Underlying right);

        /**
         * @brief Handles constructing lists.
         * @param isolate               Runtime isolate.
         * @param args                  Arguments to apply.
         */
        static Pointer::Underlying list(Isolate* isolate, const Arguments& args = {});

        /**
         * @brief Handles constructing objects.
         * @param isolate               Runtime isolate.
         * @param args                  Arguments to apply.
         */
        static Pointer::Underlying object(Isolate* isolate, const Arguments& args = {});

        /**
         * @brief Handles loading iterators.
         * @param isolate               Runtime isolate.
         * @param iterable              Iterable to load.
         */
        static Pointer::Underlying iterator(Isolate* isolate, Pointer::Underlying iterable);

        /**
         * @brief Handles constructing enumerations.
         * @param isolate               Runtime isolate.
         * @param args                  Arguments to apply.
         */
        static Pointer::Underlying enumeration(Isolate* isolate, const Arguments& args = {});

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles dispatching a recall-operation.
         * @param isolate               Runtime isolate.
         * @param frame                 Closure frame.
         * @param sink                  Output register.
         * @param target                Target to call.
         * @param args                  Arguments to apply.
         */
        static Mode m_recall(Isolate* isolate, Function::Frame* frame, Register sink, const Arguments& args = {});

        /**
         * @brief Handles dispatching a call-operation.
         * @param isolate               Runtime isolate.
         * @param frame                 Closure frame.
         * @param sink                  Output register.
         * @param target                Target to call.
         * @param args                  Arguments to apply.
         */
        static Mode m_invoke(
            Isolate* isolate, Function::Frame* frame, Register sink, Value::Any target, const Arguments& args = {});

        /**
         * @brief Handles dispatching a spawn-operation.
         * @param isolate               Runtime isolate.
         * @param frame                 Closure frame.
         * @param sink                  Output register.
         * @param target                Target to call.
         * @param args                  Arguments to apply.
         */
        static Mode m_spawn(
            Isolate* isolate, Function::Frame* frame, Register sink, Value::Any target, const Arguments& args = {});

        /**
         * @brief Handles validating feedback.
         * @param isolate               Runtime isolate.
         * @param frame                 Closure frame.
         * @param feedback              Feedback details.
         */
        static void m_feedback(Isolate* isolate, const Feedback& feedback);

        /**
         * @brief Handles getting an attribute.
         * @param isolate               Runtime isolate.
         * @param frame                 Closure frame.
         * @param target                Target to call.
         * @param index                 Index of symbol.
         */
        static Value::Any m_getter(Isolate* isolate, Value::Any target, Value::Symbol symbol);
        static Value::Any m_getter(Isolate* isolate, Function::Frame* frame, Value::Any target, Bytecode::Index index);

        /**
         * @brief Handles setting an attribute.
         * @param isolate               Runtime isolate.
         * @param frame                 Closure frame.
         * @param target                Target to call.
         * @param value                 Value to assign.
         * @param index                 Index of symbol.
         */
        static Value::Any m_setter(Isolate* isolate, Value::Any target, Value::Any value, Value::Symbol symbol);
        static Value::Any m_setter(
            Isolate* isolate, Function::Frame* frame, Value::Any target, Value::Any value, Bytecode::Index index);

        /**
         * @brief Handles concatenating strings.
         * @param isolate               Runtime isolate.
         * @param left                  Left-most value.
         * @param right                 Right-most value.
         */
        static Value::Any m_concat(Isolate* isolate, Value::Any left, Value::Any right);

        /**
         * @brief Handles constructing lists.
         * @param isolate               Runtime isolate.
         * @param args                  Arguments to apply.
         */
        static Value::Any m_list(Isolate* isolate, const std::span<Value::Any>& values = {});

        /**
         * @brief Handles constructing objects.
         * @param isolate               Runtime isolate.
         * @param args                  Arguments to apply.
         */
        static Value::Any m_object(Isolate* isolate, const std::span<Value::Any>& pairs = {});

        /**
         * @brief Resolves an iterator value.
         * @param isolate               Runtime isolate.
         * @param iterable              Iterable to resolve.
         */
        static Value::Any m_iterator(Isolate* isolate, Value::Any iterable);

        /**
         * @brief Handles constructing enumerations.
         * @param isolate               Runtime isolate.
         * @param args                  Arguments to apply.
         */
        static Value::Any m_enumeration(Isolate* isolate, const std::span<Value::Any>& tuples = {});

        /**
         * @brief Handles a jump condition.
         * @param frame                 Function frame.
         * @param index                 Index of jump.
         */
        static Mode m_jump(Function::Frame* frame, Bytecode::Index index);

        /**
         * @brief Checks if a value extends a guard.
         * @param value                 Value to check.
         * @param guard                 Incoming guard.
         */
        static Subtype m_extends(Value::Any value, Value::Any guard);
        static Value::Any m_ensure(Isolate* isolate, Value::Any value, Value::Any guard);

        /**
         * @brief Handles comparing values.
         * @param left                  Left value.
         * @param right                 Right value.
         */
        static inline int32_t m_compare(Number::Tagged left, Number::Tagged right) { return left.compare(right); }
        static inline int32_t m_compare(String::Dynamic left, String::Dynamic right) { return left.compare(right); }

        /**
         * @brief Handles executing a closure frame.
         * @param isolate               Thread isolate.
         * @param frame                 Closure frame.
         */
        static Value::Any m_execute(Isolate* isolate, Function::Frame* frame);

        /**
         * @brief Handles executing a singular instruction.
         * @param isolate               Thread isolate.
         * @param frame                 Closure frame.
         * @param instruction           Bytecode instruction.
         */
        template <Bytecode::Syllable S>
        static Mode m_execute(Isolate* isolate, Function::Frame* frame, Bytecode::Qualified<S>* instruction);
    };

}  // namespace Talos::Engine

#endif
