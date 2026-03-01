#ifndef _FORGE_OPERATOR_TRAITS_HPP
#define _FORGE_OPERATOR_TRAITS_HPP

/// Forge Modules
#include "forge/operator/kind.hpp"

namespace Forge::Operator::Traits {

    /**
     * @brief Handles resolving an operator symbol.
     * @param kind                  Kind of operator.
     */
    static inline constexpr $::String::View name(Kind kind) {
        switch (kind) {
#define FORGE_XX_TOKEN_UNARY(N, S, ...) X(N, S)
#define FORGE_XX_TOKEN_BINARY(N, S, ...) X(N, S)
#define X(N, S, ...) \
    case Kind::N: return S;
#include "forge/lexer/_defines/tokens.def"
            FORGE_XX_OPERATORS_CUSTOM(X) X(ASGN, "=")
#undef X
        }
    }

    /**
     * @brief Handles resolving an operator kind.
     * @param symbol                Operator symbol.
     */
    static inline constexpr Kind from(const $::String::View& symbol) {
        switch (XH::FNV::U64(symbol)) {
#define FORGE_XX_TOKEN_UNARY(N, S, ...) X(N, S)
#define FORGE_XX_TOKEN_BINARY(N, S, ...) X(N, S)
#define X(N, S, ...) \
    case XH::FNV::U64(S): return Kind::N;
#include "forge/lexer/_defines/tokens.def"
            FORGE_XX_OPERATORS_CUSTOM(X)
            X(ASGN, "=")  // expose assign
            default: return Kind::UNK;
#undef X
        }
    }

}  // namespace Forge::Operator::Traits

#endif
