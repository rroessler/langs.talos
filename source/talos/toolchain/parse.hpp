#ifndef _TALOS_TOOLCHAIN_PARSE_HPP
#define _TALOS_TOOLCHAIN_PARSE_HPP

/// Talos Includes
#include "talos/document/buffer.hpp"
#include "talos/forward/syntax.hpp"
#include "talos/lexer/buffer.hpp"
#include "talos/lexer/options.hpp"

namespace Talos::Toolchain {

/**
 * @brief Handles lexing a token-buffer.
 * @param buffer                Source buffer view.
 * @param options               Lexer options value.
 */
Lexer::Buffer lex(const $::String::View &buffer, const Lexer::Options &options = {});
Lexer::Buffer lex(const Document::Buffer &document, const Lexer::Options &options = {});

/**
 * @brief Handles parsing a token-buffer.
 * @param tokens                Tokens to parse.
 * @param reporter              Diagnostics reporter.
 */
$::Unique::Pointer<Syntax::Tree> parse(const Lexer::Buffer *tokens, Diagnostic::Reporter *reporter = nullptr);

} // namespace Talos::Toolchain

#endif
