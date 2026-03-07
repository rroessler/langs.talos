#ifndef _TALOS_TOOLCHAIN_PARSE_HPP
#define _TALOS_TOOLCHAIN_PARSE_HPP

/// Talos Includes
#include "talos/diagnostic/reporter.hpp"
#include "talos/document/buffer.hpp"
#include "talos/lexer/scanner.hpp"
#include "talos/syntax/tree.hpp"

namespace Talos::Toolchain {

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

}  // namespace Talos::Toolchain

#endif
