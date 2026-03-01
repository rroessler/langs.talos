#ifndef _FORGE_LEXER_KIND_HPP
#define _FORGE_LEXER_KIND_HPP

/// Forge Modules
#include "forge/forward/lexer.hpp"

namespace Forge::Lexer {

    /// @brief Available Token Kinds.
    enum class Kind : uint8_t {
#define FORGE_XX_TOKEN_BASE(N, ...) N,
#include "forge/lexer/_defines/tokens.def"
    };

}  // namespace Forge::Lexer

#endif
