#ifndef _FORGE_LEXER_TRAITS_HPP
#define _FORGE_LEXER_TRAITS_HPP

/// Forge Modules
#include "forge/lexer/kind.hpp"

namespace Forge::Lexer::Traits {

    /**
     * @brief Gets the associated token name.
     * @param kind                  Token kind.
     */
    static inline $::String::View name(Kind kind) {
        switch (kind) {
#define FORGE_XX_TOKEN_BASE(N, ...) \
    case Kind::N: return #N;
#include "forge/lexer/_defines/tokens.def"
            default: return "MISC_UNK";
        }
    }

    /**
     * @brief Gets the associated token symbol.
     * @param kind                  Token kind.
     */
    static inline $::String::View symbol(Kind kind) {
        switch (kind) {
#define FORGE_XX_TOKEN_KEYWORD(N, S, ...) FORGE_XX_TOKEN_SYMBOL(N, S)
#define FORGE_XX_TOKEN_SYMBOL(N, S, ...) \
    case Kind::N: return S;
#include "forge/lexer/_defines/tokens.def"
            default: return "";
        }
    }

}  // namespace Forge::Lexer::Traits

#endif
