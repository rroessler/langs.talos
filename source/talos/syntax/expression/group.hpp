#ifndef _TALOS_EXPRESSION_GROUP_HPP
#define _TALOS_EXPRESSION_GROUP_HPP

/// Talos Modules
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

    /// @brief Group Expression.
    class Group : public Abstract<Group, Expression> {
        //  PROPERTIES  //

        /// @brief Associated statement value.
        Expression* m_value;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a grouped expression.
         * @param value                     Grouped value.
         */
        explicit Group(Expression* value) : Group(value, value->traits()->location()) {}

        /**
         * @brief Constructs a grouped expression.
         * @param value                     Grouped value.
         * @param location                  Resource location.
         */
        explicit Group(Expression* value, const Bounds& location) : Abstract(location), m_value(value) {}

        //  PUBLIC METHODS  //

        /// @brief Encpasulated panic value.
        inline constexpr Expression* value() const noexcept { return m_value; }
    };

}  // namespace Talos::Syntax

#endif
