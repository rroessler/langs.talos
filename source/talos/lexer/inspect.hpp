#ifndef _TALOS_LEXER_INSPECT_HPP
#define _TALOS_LEXER_INSPECT_HPP

/// Talos Includes
#include "talos/lexer/kind.hpp"

namespace Talos::Lexer::Inspect {

/**
 * @brief Gets the associated token name.
 * @param kind                  Token kind.
 */
$::String::View name(Kind kind);

/**
 * @brief Gets the associated token symbol.
 * @param kind                  Token kind.
 */
$::String::View symbol(Kind kind);

} // namespace Talos::Lexer::Inspect

#endif
