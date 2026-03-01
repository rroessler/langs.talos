#ifndef _FORGE_EXPRESSION_CAST_HPP
#define _FORGE_EXPRESSION_CAST_HPP

/// Forge Modules
#include "forge/syntax/node.hpp"

namespace Forge::Syntax {

    /// @brief Cast Expression Node.
    class Cast : public Abstract<Cast, Expression> {
        //  PROPERTIES  //

        /// @brief Expression value.
        Expression* m_value;

        /// @brief Expression guard.
        Annotation* m_guard;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a cast expression.
         * @param value                     Cast value.
         * @param guard                     Guard value.
         */
        explicit Cast(Expression* value, Annotation* guard) : Cast(value, guard, value->traits()->location()) {}

        /**
         * @brief Constructs a cast expression.
         * @param value                     Cast value.
         * @param guard                     Guard value.
         * @param location                  Resource location.
         */
        explicit Cast(Expression* value, Annotation* guard, const Bounds& location) :
            Abstract(location), m_value(value), m_guard(guard) {}

        //  PUBLIC METHODS  //

        inline constexpr Expression* value() const noexcept { return m_value; }
        inline constexpr Annotation* guard() const noexcept { return m_guard; }
    };

}  // namespace Forge::Syntax

#endif
