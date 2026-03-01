#ifndef _FORGE_EXPRESSION_ACCESSOR_HPP
#define _FORGE_EXPRESSION_ACCESSOR_HPP

/// Syntax Modules
#include "forge/syntax/literal/identifier.hpp"

namespace Forge::Syntax {

    /// @brief Generic Accessor Expression.
    class Accessor : public Abstract<Accessor, Expression> {
        //  PROPERTIES  //

        Identifier* m_field;   // Field token.
        Expression* m_parent;  // Parent expression.

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a property accessor.
         * @param field                     Field expression.
         * @param parent                    Parent expression.
         */
        explicit Accessor(Identifier* field, Expression* parent) :
            Accessor(field, parent, field->traits()->location()) {}

        /**
         * @brief Constructs a property accessor.
         * @param field                     Field expression.
         * @param parent                    Parent expression.
         * @param location                  Resource location.
         */
        explicit Accessor(Identifier* field, Expression* parent, const Bounds& location) :
            Abstract(location), m_field(field), m_parent(parent) {}

        //  PUBLIC METHODS  //

        inline constexpr Identifier* field() const noexcept { return m_field; }
        inline constexpr Expression* parent() const noexcept { return m_parent; }
    };

}  // namespace Forge::Syntax

#endif
