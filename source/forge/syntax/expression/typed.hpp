#ifndef _FORGE_EXPRESSION_TYPED_HPP
#define _FORGE_EXPRESSION_TYPED_HPP

/// Forge Syntax
#include "forge/syntax/annotation/generics.hpp"

namespace Forge::Syntax {

    /// @brief Typed Expression Node.
    class Typed : public Abstract<Typed, Expression> {
        //  PROPERTIES  //

        /// @brief Expression to type.
        Expression* m_value;

        /// @brief Available type-arguments.
        Specialization m_types;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a typed expression.
         * @param expression                Expression value.
         * @param arguments                 Type arguments.
         */
        explicit Typed(Expression* value, const Specialization& types) :
            Typed(value, types, value->traits()->location()) {}

        /**
         * @brief Constructs a typed expression.
         * @param value                Expression value.
         * @param arguments                 Type arguments.
         * @param location                  Resource location.
         */
        explicit Typed(Expression* value, const Specialization& types, const Bounds& location) :
            Abstract(location), m_value(value), m_types(types) {}

        //  PUBLIC METHODS  //

        inline constexpr Expression* value() const noexcept { return m_value; }
        inline constexpr const Specialization& types() const noexcept { return m_types; }
    };

}  // namespace Forge::Syntax

#endif
