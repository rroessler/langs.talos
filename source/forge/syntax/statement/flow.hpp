#ifndef _FORGE_STATEMENT_FLOW_HPP
#define _FORGE_STATEMENT_FLOW_HPP

/// Forge Modules
#include "forge/syntax/node.hpp"

namespace Forge::Syntax {

    /// @brief Break Statement.
    struct Break : public Abstract<Break, Statement> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;
    };

    /// @brief Continue Statement.
    struct Continue : public Abstract<Continue, Statement> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;
    };

    /// @brief Return Statement.
    class Return : public Abstract<Return, Statement> {
        //  PROPERTIES  //

        /// @brief Associated statement value.
        Expression* m_value;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a "return" statement.
         * @param value                     Value to return.
         * @param location                  Resource location.
         */
        explicit Return(Expression* value, const Bounds& location = {}) : Abstract(location), m_value(value) {}

        //  PUBLIC METHODS  //

        /// @brief Encpasulated return value.
        inline constexpr Expression* value() const noexcept { return m_value; }
    };

}  // namespace Forge::Syntax

#endif
