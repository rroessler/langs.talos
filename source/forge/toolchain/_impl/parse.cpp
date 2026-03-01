/// Forge Modules
#include "forge/toolchain/parse.hpp"
#include "forge/lexer/dispatch.hpp"
#include "forge/parser/dispatch.hpp"

//  PUBLIC METHODS  //

Forge::Lexer::Buffer Forge::Toolchain::lex(const $::String::View& buffer, const Lexer::Options& options) {
    return lex(Document::Buffer(buffer), options);
}

Forge::Lexer::Buffer Forge::Toolchain::lex(const Document::Buffer& document, const Lexer::Options& options) {
    auto tokens = Lexer::Buffer(options.comments);    // prepare tokens
    auto lexer = Lexer::Scanner(&document, options);  // and the lexer
    return Lexer::Dispatch::next(lexer, tokens), std::move(tokens);
}

$::Ptr::Unique<Forge::Syntax::Tree> Forge::Toolchain::parse(
    const Lexer::Buffer* tokens, Diagnostic::Reporter* reporter) {
    auto capacity = tokens->size() / 4;  // prepare a syntax tree instance
    auto tree = $::New().unique<Syntax::Tree>(capacity, reporter->resource());

    Parser::Options options = { .storage = tree.get(), .reporter = reporter };
    auto parser = $::New().unique<Parser::Stream>(tokens, options);  // prepare
    return Parser::Dispatch::stream(parser.get(), tree->statements()), std::move(tree);
}
