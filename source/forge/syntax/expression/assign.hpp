#ifndef _FORGE_ASSIGN_EXPRESSION_HPP
#define _FORGE_ASSIGN_EXPRESSION_HPP

/// Forge Modules
#include "forge/syntax/node.hpp"

namespace Forge::Syntax {

    /// @brief Assignment Node.
    class Assign : public Abstract<Assign, Expression> {
        //  PROPERTIES  //

        /// @brief Assignment value.
        Expression* m_value;

        /// @brief Identifier name.
        Expression* m_target;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an assignment node.
         * @param target                    Assignment target.
         * @param value                     Value to assign.
         */
        explicit Assign(Expression* target, Expression* value) : Assign(target, value, target->traits()->location()) {}

        /**
         * @brief Constructs an assignment node.
         * @param target                    Assignment target.
         * @param value                     Value to assign.
         * @param location                  Resource location.
         */
        explicit Assign(Expression* target, Expression* value, const Bounds& location) :
            Abstract(location), m_value(value), m_target(target) {}

        //  PUBLIC METHODS  //

        inline constexpr Expression* value() const noexcept { return m_value; }
        inline constexpr Expression* target() const noexcept { return m_target; }
    };

}  // namespace Forge::Syntax

#endif
