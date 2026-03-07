#ifndef _TALOS_TERNARY_EXPRESSION_HPP
#define _TALOS_TERNARY_EXPRESSION_HPP

/// Talos Modules
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

    /// @brief Ternary Expression Node.
    class Ternary : public Abstract<Ternary, Expression> {
        //  PROPERTIES  //

        /// @brief Conditional node.
        Expression* m_condition;

        /// @brief Assignment value.
        Expression* m_consequence;

        /// @brief Identifier name.
        Expression* m_alternative;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a ternary node.
         * @param condition                 Condition value.
         * @param consequence               Truthy result.
         * @param alternative               Falsey result.
         */
        explicit Ternary(Expression* condition, Expression* consequence, Expression* alternative) :
            Ternary(condition, consequence, alternative, condition->traits()->location()) {}

        /**
         * @brief Constructs a ternary node.
         * @param condition                 Condition value.
         * @param consequence               Truthy result.
         * @param alternative               Falsey result.
         */
        explicit Ternary(
            Expression* condition, Expression* consequence, Expression* alternative, const Bounds& location) :
            Abstract(location), m_condition(condition), m_consequence(consequence), m_alternative(alternative) {}

        //  PUBLIC METHODS  //

        inline constexpr Expression* condition() const noexcept { return m_condition; }
        inline constexpr Expression* consequence() const noexcept { return m_consequence; }
        inline constexpr Expression* alternative() const noexcept { return m_alternative; }
    };

}  // namespace Talos::Syntax

#endif
