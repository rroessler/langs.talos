#ifndef _FORGE_LITERAL_IDENTIFIER_HPP
#define _FORGE_LITERAL_IDENTIFIER_HPP

/// Forge Modules
#include "forge/syntax/node.hpp"

namespace Forge::Syntax {

    /// @brief Identifier Literal Node.
    class Identifier : public Abstract<Identifier, Expression> {
        //  PROPERTIES  //

        /// @brief Associated identifier value.
        $::String::View m_name;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a tokenized identifier.
         * @param token                 Token to bind.
         */
        explicit Identifier(const Lexer::Token* token) : Abstract(token), m_name(token->lexeme()) {}

        /**
         * @brief Constructs a named identifier.
         * @param name                  Name to bind.
         * @param location              Optional location.
         */
        explicit Identifier(const $::String::View& name, const Bounds& location = {}) :
            Abstract(location), m_name(name) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the associated value.
        inline constexpr $::String::View name() const noexcept { return m_name; }
    };

}  // namespace Forge::Syntax

#endif
