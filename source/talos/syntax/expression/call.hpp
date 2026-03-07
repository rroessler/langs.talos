#ifndef _TALOS_EXPRESSION_CALL_HPP
#define _TALOS_EXPRESSION_CALL_HPP

/// Talos Modules
#include "talos/function/policy.hpp"
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

    /// @brief Call Expression Node.
    class Call : public Abstract<Call, Expression> {
        //  PROPERTIES  //

        /// @brief Callee expression value.
        Expression* m_callee;

        /// @brief Calling arguments.
        std::vector<Expression*> m_arguments;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a call expression.
         * @param callee                    Callee value.
         * @param arguments                 Bound arguments.
         * @param location                  Resource location.
         */
        explicit Call(Expression* callee, const std::vector<Expression*>& arguments) :
            Call(callee, arguments, callee->traits()->location()) {}

        /**
         * @brief Constructs a call expression.
         * @param callee                    Callee value.
         * @param arguments                 Bound arguments.
         * @param location                  Resource location.
         */
        explicit Call(Expression* callee, const std::vector<Expression*>& arguments, const Bounds& location) :
            Abstract(location), m_callee(callee), m_arguments(arguments) {}

        //  PUBLIC METHODS  //

        inline constexpr Expression* callee() const noexcept { return m_callee; }
        inline constexpr const std::vector<Expression*>& arguments() const noexcept { return m_arguments; }
    };

}  // namespace Talos::Syntax

#endif
