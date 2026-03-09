#ifndef _TALOS_MONAD_RESULT_HPP
#define _TALOS_MONAD_RESULT_HPP

/// Talos Modules
#include "talos/forward/monad.hpp"
#include "talos/object/abstract.hpp"

/// Forward Declarations
$_FWD(Talos::Monad, Result Success(Runtime::Isolate*, Value::Any))
$_FWD(Talos::Monad, Result Failure(Runtime::Isolate*, Value::Any))

namespace Talos {

    //  TYPEDEFS  //

    /// @brief Result Object Attributes.
    template <>
    struct Object::Attributes<Monad::Result> {
        //  PROPERTIES  //

        /// @brief Denotes result typing.
        bool success = true;

        /// @brief The result value.
        Value::Any storage = Value::Void();

        //  CONSTRUCTORS  //

        /// @brief Constructs an empty result.
        explicit Attributes() = default;

        /**
         * @brief Constructs a result monad.
         * @param value             Value to bind.
         */
        explicit Attributes(Value::Any value, std::true_type) : success(true), storage(value) {}
        explicit Attributes(Value::Any value, std::false_type) : success(false), storage(value) {}
    };

    /// @brief Result Monad Interface.
    struct Monad::Result : public Object::Abstract<Monad::Result> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

        //  PUBLIC METHODS  //

        /// @brief Denotes what type of result we have.
        inline constexpr bool success() const noexcept { return m_attrs()->success; }
        inline constexpr bool failure() const noexcept { return !m_attrs()->success; }

        /// @brief Gets the underlying storage value.
        inline constexpr Value::Any storage() const noexcept { return m_attrs()->storage; }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handlers yielding results safely.
         * @param self                          Result instance.
         * @param yield                         Yield callback.
         */
        static void m_yield(const Result& self, const Globals::Each& yield);
    };

}  // namespace Talos

#endif
