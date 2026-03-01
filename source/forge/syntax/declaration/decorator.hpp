#ifndef _FORGE_DECLARATION_DECORATOR_HPP
#define _FORGE_DECLARATION_DECORATOR_HPP

/// Forge Modules
#include "forge/reflect/category.hpp"
#include "forge/syntax/node.hpp"

namespace Forge::Syntax {

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

}  // namespace Forge::Syntax

#endif
