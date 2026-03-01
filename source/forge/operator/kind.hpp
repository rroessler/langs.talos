#ifndef _FORGE_OPERATOR_KIND_HPP
#define _FORGE_OPERATOR_KIND_HPP

/// Forge Modules
#include "forge/forward/operator.hpp"
#include "forge/lexer/kind.hpp"

//  X-MACROS  //

#define FORGE_XX_OPERATORS_CUSTOM(X) \
    X(CALL, "call", = UINT8_MAX + 1) \
    X(ITER, "iter")                  \
    X(UNK, "unknown", = UINT16_MAX)

//  NAMESPACES  //

namespace Forge::Operator {

    /// @brief Available Operator Kinds.
    enum class Kind : uint16_t {
        ASGN = static_cast<uint16_t>(Lexer::Kind::ASOP_DEF),
        NEG = static_cast<uint16_t>(Lexer::Kind::BINOP_SUB),
#define FORGE_XX_TOKEN_UNARY(N, ...) N = static_cast<uint16_t>(Lexer::Kind::UNOP_##N),
#define FORGE_XX_TOKEN_BINARY(N, ...) N = static_cast<uint16_t>(Lexer::Kind::BINOP_##N),
#include "forge/lexer/_defines/tokens.def"

#define X(K, _, ...) K __VA_ARGS__,
        FORGE_XX_OPERATORS_CUSTOM(X)
#undef X
    };

    /// @brief Unary Operator Validation.
    static inline constexpr bool Unary(Kind kind) {
        return
#define FORGE_XX_TOKEN_UNARY(N, ...) (kind == Kind::N) ||
#include "forge/lexer/_defines/tokens.def"
            (kind == Kind::NEG) || (kind == Kind::CALL) || (kind == Kind::ITER);
    }

    /// @brief Binary Operator Validation.
    static inline constexpr bool Binary(Kind kind) {
        return
#define FORGE_XX_TOKEN_BINARY(N, ...) (kind == Kind::N) ||
#include "forge/lexer/_defines/tokens.def"
            (kind == Kind::ASGN);
    }

    /// @brief Comparator Operator Validation.
    static inline constexpr bool Comparable(Kind kind) {
        return
#define FORGE_XX_TOKEN_COMPARE(N, ...) (kind == Kind::N) ||
#include "forge/lexer/_defines/tokens.def"
            false;
    }

    /// @brief Assignment Operator Validation.
    static inline constexpr bool Assignable(Kind kind) {
        return
#define FORGE_XX_TOKEN_ASSIGN(N, ...) (kind == Kind::N) ||
#include "forge/lexer/_defines/tokens.def"
            (kind == Kind::ASGN);
    }

}  // namespace Forge::Operator

#endif
