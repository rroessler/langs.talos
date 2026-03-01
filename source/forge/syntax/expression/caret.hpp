#ifndef _FORGE_EXPRESSION_CARET_HPP
#define _FORGE_EXPRESSION_CARET_HPP

/// Forge Modules
#include "forge/syntax/node.hpp"

namespace Forge::Syntax {

    /// @brief Caret Expression Node.
    struct Caret : public Abstract<Caret, Expression> {
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a caret expression.
         * @param token                 Caret token.
         */
        explicit Caret(const Lexer::Token* token) : Caret(token->location()) {
            $_ASSERT(token->kind() == Lexer::Kind::BINOP_XOR);
        }

        /**
         * @brief Constructs a caret expression.
         * @param location              Optional location.
         */
        explicit Caret(const Bounds& location = {}) : Abstract(location) {}
    };

}  // namespace Forge::Syntax

#endif
