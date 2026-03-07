#ifndef _TALOS_OPERATOR_TRAITS_HPP
#define _TALOS_OPERATOR_TRAITS_HPP

/// Talos Modules
#include "talos/operator/kind.hpp"

namespace Talos::Operator::Traits {

    /**
     * @brief Handles resolving an operator symbol.
     * @param kind                  Kind of operator.
     */
    static inline constexpr $::String::View name(Kind kind) {
        switch (kind) {
#define TALOS_XX_TOKEN_UNARY(N, S, ...) X(N, S)
#define TALOS_XX_TOKEN_BINARY(N, S, ...) X(N, S)
#define X(N, S, ...) \
    case Kind::N: return S;
#include "talos/lexer/_defines/tokens.def"
            TALOS_XX_OPERATORS_CUSTOM(X) X(ASGN, "=")
#undef X
        }
    }

    /**
     * @brief Handles resolving an operator kind.
     * @param symbol                Operator symbol.
     */
    static inline constexpr Kind from(const $::String::View& symbol) {
        switch (XH::FNV::U64(symbol)) {
#define TALOS_XX_TOKEN_UNARY(N, S, ...) X(N, S)
#define TALOS_XX_TOKEN_BINARY(N, S, ...) X(N, S)
#define X(N, S, ...) \
    case XH::FNV::U64(S): return Kind::N;
#include "talos/lexer/_defines/tokens.def"
            TALOS_XX_OPERATORS_CUSTOM(X)
            X(ASGN, "=")  // expose assign
            default: return Kind::UNK;
#undef X
        }
    }

}  // namespace Talos::Operator::Traits

#endif
