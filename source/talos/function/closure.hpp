#ifndef _TALOS_FUNCTION_CLOSURE_HPP
#define _TALOS_FUNCTION_CLOSURE_HPP

/// Talos Modules
#include "talos/function/context.hpp"
#include "talos/function/info.hpp"
#include "talos/object/abstract.hpp"

namespace Talos {

    /// @brief Closure Function Attributes.
    template <>
    struct Object::Attributes<Function::Closure> {
        //  PROPERTIES  //

        /// @brief Shared function information.
        const Function::Info* info;

        /// @brief Bound function environment.
        Function::Context context = Function::Context();

        //  CONSTRUCTORS  //

        /// @brief Do not allow default construction.
        explicit Attributes() = delete;

        /**
         * @brief Constructs a closure.
         * @param info              Closure information.
         * @param context           Context to be bound.
         */
        explicit Attributes(const Function::Info* info) : Attributes(info, Value::Void()) {}
        explicit Attributes(const Function::Info* info, Value::Any context) : info(info), context(context) {}
    };

    /// @brief Closure Function Interface.
    struct Function::Closure : public Object::Abstract<Function::Closure> {
        //  TYPEDEFS  //

        /// @brief Allow base function access.
        friend struct Dynamic;

        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

        //  PUBLIC METHODS  //

        inline constexpr const Context& context() const { return m_attrs()->context; }
        inline constexpr const Info* info() const noexcept { return m_attrs()->info; }

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
         * @brief Handlers yielding closures safely.
         * @param self                          Closure instance.
         * @param yield                         Yield callback.
         */
        static void m_yield(const Closure& self, const Globals::Each& yield);
    };

}  // namespace Talos

#endif
