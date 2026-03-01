#ifndef _FORGE_BYTECODE_COMPILER_HPP
#define _FORGE_BYTECODE_COMPILER_HPP

/// Forge Modules
#include "forge/bytecode/assembler.hpp"
#include "forge/bytecode/binder.hpp"
#include "forge/bytecode/loop.hpp"
#include "forge/bytecode/optimizer.hpp"
#include "forge/bytecode/request.hpp"
#include "forge/bytecode/trace.hpp"
#include "forge/diagnostic/traits.hpp"
#include "forge/function/info.hpp"
#include "forge/variable/captures.hpp"

/// Syntax Modules
#include "forge/syntax/literal/identifier.hpp"

namespace Forge::Bytecode {

    /// @brief Variable Declaration Typing.
    using Declaration = std::pair<Register, bool>;

    /// @brief Bytecode Compiler.
    class Compiler : public XI::Define<Compiler, XI::Unique> {
        //  PROPERTIES  //

        /// @brief Current compilation request.
        Request* m_request = nullptr;

        /// @brief Underlying services container.
        XI::Container* m_services = nullptr;

        /// @brief The current stack-traces.
        Trace::Stack m_traces = {};

        /// @brief The current bytecode arena.
        $::Ptr::Unique<Linker::Arena> m_arena = nullptr;

        /// @brief Associated variable captures.
        const Variable::Captures* m_captures = nullptr;

        /// @brief The bytecode assembler service.
        $::Ptr::Unique<Assembler> m_assembler = nullptr;

        /// @brief The bytecode optimizer service.
        $::Ptr::Unique<Optimizer> m_optimizer = nullptr;

        /// @brief Current compilation pipeline.
        $::Ptr::Unique<Queue> m_queue = $::New().unique<Queue>();

        /// @brief The binder for blocks/jumps labels.
        $::Ptr::Unique<Binder> m_labels = $::New().unique<Binder>(&m_request);

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a bytecode compiler.
        explicit Compiler();

        /**
         * @brief Constructs a bytecode compiler.
         * @param services                  Services container.
         */
        explicit Compiler(XI::Container* services);

        //  PUBLIC METHODS  //

        inline constexpr bool bundled() const noexcept { return m_bundled(); }
        inline constexpr Binder* labels() const noexcept { return m_labels.get(); }
        inline constexpr const Queue* queue() const noexcept { return m_queue.get(); }
        inline constexpr $::URI::View resource() const noexcept { return m_arena->resource; }
        inline constexpr Routine* routine() const noexcept { return m_request->routine(); }
        inline constexpr const Variable::Captures* captures() const noexcept { return m_captures; }
        inline constexpr Allocator* registers() const noexcept { return m_request->registers(); }
        inline constexpr Variable::Context* variables() const noexcept { return m_request->variables(); }

        /// @brief Constructs a variable scoping.
        inline constexpr auto scope() { return m_request->scope(); }

        /// @brief Constructs a scoped loop.
        inline constexpr Loop loop() { return Loop(this); }

        /**
         * @brief Handles tracing positions.
         * @param position              Position to trace.
         */
        inline constexpr Trace trace(const Linker::Position& position) { return Trace(&m_traces, position); }

        /**
         * @brief Handles tracing nodes.
         * @param node                  Node to trace.
         */
        inline constexpr Trace trace(const Syntax::Node* node) {
            return node->is<Syntax::Lambda>() ? Trace() : trace(node->traits()->range().start);
        }

        /**
         * @brief Constructs a constant value.
         * @param value                     Value to make constant.
         */
        Index constant(Value::Any value);

        /**
         * @brief Constructs a string intern.
         * @param buffer                    Buffer to intern.
         */
        Index string(const $::String::View& buffer);

        /**
         * @brief Constructs a string/symbol intern.
         * @param buffer                    Buffer to intern.
         */
        Index symbol(const $::String::View& buffer);

        /**
         * @brief Handles enqueuing functions for compilation.
         * @param function                  Function to compile.
         */
        Index enqueue(const Syntax::Lambda* function) const;

        /**
         * @brief Constructs an import path intern.
         * @param sink                      Destination register.
         * @param buffer                    Buffer to intern.
         */
        void import(Destination sink, const $::String::View& buffer);

        /**
         * @brief Handles loading/storing variables.
         * @param name                      Name of variable.
         * @param extent                    Variable extent.
         */
        void load(const $::String::View& name, Variable::Extent extent, Destination sink);
        void store(const $::String::View& name, Variable::Extent extent, Register value);

        /**
         * @brief Handles lowering the incoming node.
         * @param node                      Node to lower.
         * @param destination               Destination to use.
         */
        void lower(const Syntax::Node* node, Destination destination = {});

        /**
         * @brief Handles emitting preamble information.
         * @param preamble                  Preamble node.
         * @param value                     Source of preamble.
         */
        void preamble(const Syntax::Preamble* preamble, Register value);
        void expose(const Syntax::Declaration* declaration, Register value);

        /**
         * @brief Handles compiling syntax trees.
         * @param syntax                    Syntax to compile.
         * @param captures                  Variable captures.
         */
        $::Ptr::Unique<Linker::Arena> process(const Syntax::Tree* syntax, const Variable::Captures* captures);

        /**
         * @brief Handles declaring a variable.
         * @param variable                  Variable to declare.
         */
        inline Declaration declare(const Syntax::Identifier* variable) { return declare(variable->name(), variable); }
        inline Declaration declare(const Syntax::Declaration* variable) { return declare(variable->name(), variable); }

        /**
         * @brief Handles declaring a variable.
         * @param name                      Name of variable.
         * @param node                      Associated node.
         */
        inline Declaration declare(const $::String::View& name, const Syntax::Node* node) {
            auto leaked = m_captures->resolve(node) == Variable::Extent::LEAKED;
            auto vreg = leaked ? Register(routine()->shared->leaked++) : registers()->allocate();
            return variables()->declare(name, vreg, leaked), Declaration(vreg, leaked);
        }

        /**
         * @brief Handles returning with a value.
         * @param value                     Value to panic.
         */
        inline void returns(const Syntax::Expression* value) { lower(value, Accumulator()), m_returns(); }

        /**
         * @brief Handles panicking with a value.
         * @param value                     Value to panic.
         */
        inline void panic(const Syntax::Expression* value) { lower(value, Accumulator()), m_panic(); }

        /**
         * @brief Handles emitting panics.
         * @param code                      Diagnostic code.
         * @param args                      Format arguments.
         */
        template <class... As>
        inline void panic(Diagnostic::Code code, As&&... args) {
            panic(Diagnostic::Traits::format(code, std::forward<As>(args)...));
        }

        /**
         * @brief Handles emitting panics.
         * @param code                      Diagnostic code.
         * @param args                      Format arguments.
         */
        template <class... As>
        inline void panic(const $::String::View& message, As&&... args) {
            auto formatted = fmt::format(fmt::runtime(message), std::forward<As>(args)...);
            emit<Syllable::STRING_MAKE>(Accumulator(), string(formatted)), m_panic();
        }

        /**
         * @brief Emits an instruction to the current block.
         * @param operands                  Operands to emit.
         */
        template <Syllable S, class... As>
        inline constexpr void emit(As&&... operands) {
            m_emit(Qualified<S>(std::forward<As>(operands)...).encode());
        }

        /**
         * @brief Handles plugging instructions.
         * @param destination           Destination register.
         * @param operands              Instruction operands.
         */
        template <Syllable S, class... As>
        inline constexpr void plug(const Destination& destination, As&&... operands) {
            if (!destination.nowhere()) emit<S>(destination, std::forward<As>(operands)...);
        }

       private:
        //  PRIVATE METHODS  //

        /// @brief Denotes if the runtime is being bundled.
        bool m_bundled() const noexcept;

        /**
         * @brief Handles emitting an instruction.
         * @param instruction               Instruction to emit.
         */
        void m_emit(const Instruction& instruction);

        /**
         * @brief Handles compiling a function request.
         * @param request                   Bytecode request.
         */
        void m_function(Request* request);

        /**
         * @brief Handles compiling a function parameter.
         * @param parameter                 Parameter to compile.
         * @param spread                    Expected spread parameter.
         */
        bool m_parameter(const Syntax::Variable* parameter, const Syntax::Variable* spread = nullptr);

        /// @brief Handles internal returning from the accumulator.
        inline void m_returns() { emit<Syllable::EXEC_RETURN>(), emit<Syllable::JUMP_TO>(m_labels->returns()); }

        /// @brief Handles internal panicking from the accumulator.
        inline void m_panic() { emit<Syllable::EXEC_PANIC>(), emit<Syllable::JUMP_TO>(m_labels->returns()); }
    };

}  // namespace Forge::Bytecode

#endif
