#ifndef _TALOS_DECLARATION_DECORATOR_HPP
#define _TALOS_DECLARATION_DECORATOR_HPP

/// Talos Modules
#include "talos/reflect/category.hpp"
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

    /// @brief Runtime Decorator Node.
    class Decorator : public Abstract<Decorator> {
        //  PROPERTIES  //

        /// @brief Bound decoration value.
        Expression* m_expression;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a runtime decorator.
         * @param expression                Value to encapsulate.
         */
        explicit Decorator(Expression* expression) : Decorator(expression, expression->traits()->location()) {}

        /**
         * @brief Constructs a runtime decorator.
         * @param expression                Value to encapsulate.
         */
        explicit Decorator(Expression* expression, const Bounds& location) :
            Abstract(location), m_expression(expression) {}

        //  PUBLIC METHODS  //

        /// @brief The decorator expression to be called.
        inline constexpr Expression* expression() const noexcept { return m_expression; }
    };

}  // namespace Talos::Syntax

#endif
