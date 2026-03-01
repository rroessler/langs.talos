#ifndef _FORGE_EXPRESSION_PANIC_HPP
#define _FORGE_EXPRESSION_PANIC_HPP

/// Forge Modules
#include "forge/syntax/node.hpp"

namespace Forge::Syntax {

    /// @brief Panic Expression.
    class Panic : public Abstract<Panic, Expression> {
        //  PROPERTIES  //

        /// @brief Associated statement value.
        Expression* m_value;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a "panic" expression.
         * @param value                     Failure value.
         * @param location                  Resource location.
         */
        explicit Panic(Expression* value, const Bounds& location = {}) : Abstract(location), m_value(value) {}

        //  PUBLIC METHODS  //

        /// @brief Encpasulated panic value.
        inline constexpr Expression* value() const noexcept { return m_value; }
    };

}  // namespace Forge::Syntax

#endif
