/// Talos Includes
#include "talos/toolchain/parse.hpp"
#include "talos/diagnostic/reporter.hpp"
#include "talos/lexer/dispatch.hpp"
#include "talos/parser/dispatch.hpp"
#include "talos/parser/stream.hpp"
#include "talos/syntax/tree.hpp"
#include "talos/variable/analyzer.hpp"

//  PUBLIC METHODS  //

Talos::Lexer::Buffer Talos::Toolchain::lex(const Document::Buffer &document, const Lexer::Options &options) {
  return lex(document.view(), options);
}

Talos::Lexer::Buffer Talos::Toolchain::lex(const $::String::View &buffer, const Lexer::Options &options) {
  auto tokens = Lexer::Buffer(options.comments);
  auto lexer = Lexer::Scanner(buffer, options);
  return Lexer::Dispatch::next(lexer, tokens), tokens;
}

$::Unique::Pointer<Talos::Syntax::Tree>
Talos::Toolchain::parse(const Lexer::Buffer *tokens, Diagnostic::Reporter *reporter) {
  // prepare a suitable tree and parser to be used
  auto tree = $::Unique::New<Syntax::Tree>(tokens->buffer(), reporter->resource());
  auto parser = $::Unique::New<Parser::Stream>(tokens, tree.get(), reporter);

  // attempt parsing the tree then ensure we also visit marks
  Parser::Dispatch::stream(parser.get(), tree->statements());
  return Variable::Analyzer().visit(tree.get()), std::move(tree);
}
