#ifndef _TALOS_MACHINE_EMITTER_HPP
#define _TALOS_MACHINE_EMITTER_HPP

/// Talos Modules
#include "talos/engine/register.hpp"
#include "talos/forward/diagnostic.hpp"
#include "talos/forward/machine.hpp"
#include "talos/value/void.hpp"

/// Forward Declarations
$_FWD(static inline constexpr bool FAST = true, Talos::Machine::Validate)
$_FWD(static inline constexpr bool SLOW = false, Talos::Machine::Validate)

namespace Talos::Machine {

    /// @brief Machine-Code Emitter.
    class Emitter {
        //  PROPERTIES  //

        /// @brief The current
        size_t m_offset = 0;

        /// @brief Underlying builder instance.
        Builder* m_builder = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Do not allow default construction.
        explicit Emitter() = default;

        /**
         * @brief Constructs an emitter instance.
         * @param builder           Builder to bind.
         */
        explicit Emitter(Builder* builder) : m_builder(builder) {}

        //  PUBLIC METHODS  //

        /**
         * @brief Constructs memory pointers.
         * @param vreg               Virtual register.
         * @param offset             Alignment offset.
         */
        Memory memory(const Register& vreg, size_t offset = 0) const noexcept;

        /**
         * @brief Allows casting values to immediates.
         * @param value             Value to cast.
         */
        Immediate immediate(Value::Any value) const noexcept;

        /**
         * @brief Converts an intern into a register.
         * @param index             Index of intern.
         */
        Register intern(const Bytecode::Index& index) noexcept;

        /**
         * @brief Handles loading a string.
         * @param vreg              Virtual register.
         * @param intern            String intern.
         */
        Register string(const Bytecode::Index& index) noexcept;
        Register string(const String::Intern* intern) noexcept;
        void string(const Register& vreg, const Bytecode::Index& index) noexcept;
        void string(const Register& vreg, const String::Intern* intern) noexcept;
        void string(const Engine::Register& vreg, const Bytecode::Index& index) noexcept;
        void string(const Engine::Register& vreg, const String::Intern* intern) noexcept;

        /**
         * @brief Handles resolving a bytecode register.
         * @param vreg              Bytecode register.
         */
        Register resolve(const Engine::Register& vreg);

        /**
         * @brief Sets the current label offset.
         * @param offset            Offset to bind.
         */
        Label label(size_t offset);

        /**
         * @brief Resolve a label relative to a jump.
         * @param index             Jump index.
         */
        Label label(const Bytecode::Index& index);

        /**
         * @brief Tests for truthiness.
         * @param vreg              Register to test.
         */
        Label truthy(const Register& vreg);
        Label truthy(const Engine::Register& vreg);
        void truthy(const Label& label, const Register& vreg);
        void truthy(const Label& label, const Engine::Register& vreg);

        /**
         * @brief Tests for falsiness.
         * @param vreg              Register to test.
         */
        Label falsey(const Register& vreg);
        Label falsey(const Engine::Register& vreg);
        void falsey(const Label& label, const Register& vreg);
        void falsey(const Label& label, const Engine::Register& vreg);

        /**
         * @brief Handles converting values to floats.
         * @param label             Bailout label.
         * @param xmm               Float register.
         * @param tx                Value register.
         * @param tv                Value bytecode.
         */
        void vtof(const Label& label, const Double& xmm, const Register& tx);
        void vtof(const Label& label, const Double& xmm, const Register& tx, const Engine::Register& tv);

        /**
         * @brief Handles converting floats to values.
         * @param xmm                Float register.
         * @param tx                 Value register.
         */
        void ftov(const Double& xmm, const Register& tx);

        /**
         * @brief Loads a value onto the given register.
         * @param vreg              Register to return.
         * @param value             Value to return.
         */
        void load(Value::Any value);
        void load(const Register& vreg, Value::Any value);
        void load(const Engine::Register& vreg, Value::Any value);

        /**
         * @brief Handles moving registers.
         * @param dst               Destination register.
         * @param src               Source register.
         */
        void move(const Register& dst, const Register& src);
        void move(const Register& dst, const Engine::Register& src);
        void move(const Engine::Register& dst, const Register& src);
        void move(const Engine::Register& dst, const Engine::Register& src);

        /**
         * @brief Handles printing registers for debugging.
         * @param vreg              Register to print.
         * @param pretty            Prettiness flag.
         */
        void expose(const Register& vreg, bool pretty = false);
        void expose(const Engine::Register& vreg, bool pretty = false);

        /// @brief Emits a no-operation (eg: does nothing).
        inline constexpr void noop() const noexcept {}

        /**
         * @brief Returns from a given register.
         * @param vreg              Register to return.
         * @param value             Value to return.
         */
        void returns();
        void returns(Value::Any value);
        void returns(const Register& vreg);
        void returns(const Register& vreg, Value::Any value);

        /**
         * @brief Forces an interrupt to occur.
         * @param condition             Condition register.
         */
        void interrupt();
        void interrupt(const Register& condition);

        /**
         * @brief Validates a register to not be an error.
         * @param vreg              Register to validate.
         * @param fast              Expecting a fast check.
         */
        void validate(const Register& vreg, bool fast = Validate::SLOW);
        void validate(const Engine::Register& vreg, bool fast = Validate::SLOW);

        /**
         * @brief Preloads passthrough parameters.
         * @param self              Register self.
         * @param span              Register span.
         */
        void parameters();
        void parameters(const Engine::Register& self);
        void parameters(const Engine::Register::Span& span);
        void parameters(const Engine::Register& self, const Engine::Register::Span& span);

        /**
         * @brief Handles invoking functions.
         * @param callback          Callback to call.
         * @param args              Arguments to bind.
         */
        template <class F, class... As>
        inline constexpr XASM::Function::Callee* invoke(F callback, As&&... args) {
            return XASM::Function::Invoke(m_compiler(), callback, std::forward<As>(args)...);
        }

        /// @brief Pads header spacing as necessary.
        inline constexpr void header() { m_header(""); }

        /**
         * @brief Handles emitting inline comments.
         * @param fmt               Message format.
         * @param args              Comment arguments.
         */
        template <class... As>
        inline constexpr void header(fmt::format_string<As...> fmt, As&&... args) {
            m_header("\n; " + fmt::format(fmt, std::forward<As>(args)...));
        }

        /**
         * @brief Handles emitting inline comments.
         * @param fmt               Message format.
         * @param args              Comment arguments.
         */
        template <class... As>
        inline constexpr void comment(fmt::format_string<As...> fmt, As&&... args) {
            m_comment(fmt::format(fmt, std::forward<As>(args)...));
        }

       private:
        //  PRIVATE METHODS  //

        /// @brief Gets the underlying compiler instance.
        Compiler* m_compiler() noexcept;

        /**
         * @brief Handles loading arguments to a register.
         * @param vreg              Virtual register.
         * @param offset            Argument offset.
         */
        void m_argv(const Register& vreg, size_t offset = 0);

        /**
         * @brief Constructs comments.
         * @param message           Message to bind.
         */
        void m_header(const $::String::View& message);
        void m_comment(const $::String::View& message);

        /**
         * @brief Converts an index to a string intern.
         * @param index             Index to convert.
         */
        const String::Intern* m_intern(const Bytecode::Index& index) const noexcept;
    };

}  // namespace Talos::Machine

#endif
