#ifndef _TALOS_EXPRESSION_PANIC_HPP
#define _TALOS_EXPRESSION_PANIC_HPP

/// Talos Modules
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

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

}  // namespace Talos::Syntax

#endif
