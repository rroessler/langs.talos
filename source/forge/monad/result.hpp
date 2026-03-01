#ifndef _FORGE_MONAD_RESULT_HPP
#define _FORGE_MONAD_RESULT_HPP

/// Forge Modules
#include "forge/forward/monad.hpp"
#include "forge/object/abstract.hpp"

/// Forward Declarations
$_FWD(Result Success(Runtime::Isolate*, Value::Any), Forge::Monad)
$_FWD(Result Failure(Runtime::Isolate*, Value::Any), Forge::Monad)

namespace Forge {

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

}  // namespace Forge

#endif
