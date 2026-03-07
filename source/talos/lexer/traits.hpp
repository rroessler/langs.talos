#ifndef _TALOS_LEXER_TRAITS_HPP
#define _TALOS_LEXER_TRAITS_HPP

/// Talos Modules
#include "talos/lexer/kind.hpp"

namespace Talos::Lexer::Traits {

    /**
     * @brief Gets the associated token name.
     * @param kind                  Token kind.
     */
    static inline $::String::View name(Kind kind) {
        switch (kind) {
#define TALOS_XX_TOKEN_BASE(N, ...) \
    case Kind::N: return #N;
#include "talos/lexer/_defines/tokens.def"
            default: return "MISC_UNK";
        }
    }

    /**
     * @brief Gets the associated token symbol.
     * @param kind                  Token kind.
     */
    static inline $::String::View symbol(Kind kind) {
        switch (kind) {
#define TALOS_XX_TOKEN_KEYWORD(N, S, ...) TALOS_XX_TOKEN_SYMBOL(N, S)
#define TALOS_XX_TOKEN_SYMBOL(N, S, ...) \
    case Kind::N: return S;
#include "talos/lexer/_defines/tokens.def"
            default: return "";
        }
    }

}  // namespace Talos::Lexer::Traits

#endif
