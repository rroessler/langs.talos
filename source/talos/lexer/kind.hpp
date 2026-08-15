#ifndef _TALOS_LEXER_KIND_HPP
#define _TALOS_LEXER_KIND_HPP

/// Talos Includes
#include "talos/forward/lexer.hpp"

namespace Talos::Lexer {

/// @brief Available Token Kinds.
enum class Kind : uint8_t {
#define TALOS_XX_TOKEN_BASE(N, ...) N,
#include "talos/lexer/_defines/tokens.def"
};

} // namespace Talos::Lexer

#endif
