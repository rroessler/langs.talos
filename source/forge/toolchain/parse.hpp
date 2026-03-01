#ifndef _FORGE_TOOLCHAIN_PARSE_HPP
#define _FORGE_TOOLCHAIN_PARSE_HPP

/// Forge Includes
#include "forge/diagnostic/reporter.hpp"
#include "forge/document/buffer.hpp"
#include "forge/lexer/scanner.hpp"
#include "forge/syntax/tree.hpp"

namespace Forge::Toolchain {

    /**
     * @brief Handles lexing a token-buffer.
     * @param buffer                Source buffer view.
     * @param options               Lexer options value.
     */
    Lexer::Buffer lex(const $::String::View& buffer, const Lexer::Options& options = {});
    Lexer::Buffer lex(const Document::Buffer& document, const Lexer::Options& options = {});

    /**
     * @brief Handles parsing a token-buffer.
     * @param tokens                Tokens to parse.
     * @param reporter              Diagnostics reporter.
     */
    $::Ptr::Unique<Syntax::Tree> parse(const Lexer::Buffer* tokens, Diagnostic::Reporter* reporter = nullptr);

}  // namespace Forge::Toolchain

#endif
