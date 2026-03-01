#ifndef _FORGE_STATEMENT_CONDITIONAL_HPP
#define _FORGE_STATEMENT_CONDITIONAL_HPP

/// Forge Modules
#include "forge/syntax/node.hpp"

namespace Forge::Syntax {

    /// @brief Conditional Statement.
    class Conditional : public Abstract<Conditional, Statement> {
        //  PROPERTIES  //

        /// @brief Truthy consequence.
        Node* m_consequence;

        /// @brief Falsey alternative.
        Node* m_alternative;

        /// @brief Conditional expression.
        Expression* m_condition;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a block statement.
         * @param condition                 Base condition.
         * @param consequence               Truthy block.
         * @param alternative               Falsey block.
         * @param location                  Resource location.
         */
        explicit Conditional(Expression* condition, Node* consequence, Node* alternative, const Bounds& location = {}) :
            Abstract(location), m_consequence(consequence), m_alternative(alternative), m_condition(condition) {}

        //  PUBLIC METHODS  //

        inline constexpr Node* consequence() const noexcept { return m_consequence; }
        inline constexpr Node* alternative() const noexcept { return m_alternative; }
        inline constexpr Expression* condition() const noexcept { return m_condition; }
    };

}  // namespace Forge::Syntax

#endif
