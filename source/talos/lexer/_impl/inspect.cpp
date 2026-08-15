/// Talos Includes
#include "talos/lexer/inspect.hpp"

$::String::View Talos::Lexer::Inspect::name(Kind kind) {
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
$::String::View Talos::Lexer::Inspect::symbol(Kind kind) {
  switch (kind) {
#define TALOS_XX_TOKEN_KEYWORD(N, S, ...) TALOS_XX_TOKEN_SYMBOL(N, S)
#define TALOS_XX_TOKEN_SYMBOL(N, S, ...) \
  case Kind::N: return S;
#include "talos/lexer/_defines/tokens.def"
  default: return "";
  }
}
