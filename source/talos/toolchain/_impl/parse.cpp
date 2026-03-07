/// Talos Modules
#include "talos/toolchain/parse.hpp"
#include "talos/lexer/dispatch.hpp"
#include "talos/parser/dispatch.hpp"

//  PUBLIC METHODS  //

Talos::Lexer::Buffer Talos::Toolchain::lex(const $::String::View& buffer, const Lexer::Options& options) {
    return lex(Document::Buffer(buffer), options);
}

Talos::Lexer::Buffer Talos::Toolchain::lex(const Document::Buffer& document, const Lexer::Options& options) {
    auto tokens = Lexer::Buffer(options.comments);    // prepare tokens
    auto lexer = Lexer::Scanner(&document, options);  // and the lexer
    return Lexer::Dispatch::next(lexer, tokens), std::move(tokens);
}

$::Ptr::Unique<Talos::Syntax::Tree> Talos::Toolchain::parse(
    const Lexer::Buffer* tokens, Diagnostic::Reporter* reporter) {
    auto capacity = tokens->size() / 4;  // prepare a syntax tree instance
    auto tree = $::New().unique<Syntax::Tree>(capacity, reporter->resource());

    Parser::Options options = { .storage = tree.get(), .reporter = reporter };
    auto parser = $::New().unique<Parser::Stream>(tokens, options);  // prepare
    return Parser::Dispatch::stream(parser.get(), tree->statements()), std::move(tree);
}
