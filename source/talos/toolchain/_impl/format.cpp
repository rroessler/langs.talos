/// Talos Includes
#include "talos/toolchain/format.hpp"
#include "talos/diagnostic/reporter.hpp"
#include "talos/format/pipeline.hpp"
#include "talos/syntax/tree.hpp"
#include "talos/toolchain/parse.hpp"

//  PUBLIC METHODS  //

Talos::Format::Result Talos::Toolchain::format(const Document::Buffer &document, const Format::Options &options) {
  return format(document.view(), options);
}

Talos::Format::Result Talos::Toolchain::format(const $::String::View &buffer, const Format::Options &options) {
  // prepare an empty reporter to be used
  auto reporter = Diagnostic::Reporter();

  // prepare the lexer options to be used
  Lexer::Options lexer = {.comments = true, .reporter = &reporter};

  // parse our tokens and our syntax-tree to be used for formatting
  auto tokens = lex(buffer, lexer);

  // fail early when there are syntax errors found
  if (reporter.failed()) return std::nullopt;

  // construct a formatting pipeline to handle our document
  return Format::Pipeline(&options).process(&tokens);
}
