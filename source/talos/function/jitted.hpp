#ifndef _TALOS_FUNCTION_JITTED_HPP
#define _TALOS_FUNCTION_JITTED_HPP

/// Talos Modules
#include "talos/function/context.hpp"
#include "talos/machine/info.hpp"
#include "talos/object/abstract.hpp"

namespace Talos {

    /// @brief Jitted Function Attributes.
    template <>
    struct Object::Attributes<Function::Jitted> {
        //  PROPERTIES  //

        /// @brief The compiled machine code information.
        const Machine::Info* info = nullptr;

        /// @brief Bound function environment.
        Function::Context context = Function::Context();

        //  CONSTRUCTORS  //

        /// @brief Constructs an empty jitted function.
        explicit Attributes() = default;

        /**
         * @brief Constructs a jitted function.
         * @param info                  Machine callee.
         * @param context               Context to bind.
         */
        explicit Attributes(const Machine::Info* info, Value::Any context) : info(info), context(context) {}
    };

    /// @brief Jitted Function Interface.
    struct Function::Jitted : public Object::Abstract<Function::Jitted> {
        //  TYPEDEFS  //

        /// @brief Allow base function access.
        friend struct Dynamic;

        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

        //  PUBLIC METHODS  //

        inline constexpr const Context& context() const { return m_attrs()->context; }
        inline constexpr const Machine::Info* info() const noexcept { return m_attrs()->info; }

        inline constexpr uint64_t arity() const noexcept { return info()->arity(); }
        inline constexpr uint64_t adicity() const noexcept { return info()->adicity(); }
        inline constexpr $::URI::View resource() const noexcept { return info()->resource(); }

        /// @brief Gets the available self receiver.
        inline constexpr Value::Any receiver() const noexcept {
            auto context = m_attrs()->context;  // prepare context
            return context.valid() ? context.self() : Value::Void();
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handlers yielding jitted functions safely.
         * @param self                          Jitted instance.
         * @param yield                         Yield callback.
         */
        static void m_yield(const Jitted& self, const Globals::Each& yield);
    };

}  // namespace Talos

#endif
