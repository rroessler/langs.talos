/// Talos Includes
#include "talos/parser/delimited.hpp"

/// Syntax Includes
#include "talos/syntax/_inline/annotation.ipp"

//  PRIVATE METHODS  //

TALOS_MM_PARSE_HINT(Interface, parser) {
  // prepare some details for the enclosing parser
  static constexpr auto s_opening = Lexer::Kind::PUNC_LBRACE;
  static constexpr auto s_closing = Lexer::Kind::PUNC_RBRACE;
  static constexpr auto s_separator = Lexer::Kind::PUNC_TERM;
  static constexpr auto s_callback = [](auto *_) { return m_variable(_, true); };
  static auto s_enclosed = Enclosed<Syntax::Variable, s_opening, s_closing, s_separator>(s_callback);

  // get the snapshot to be used now
  auto snapshot = parser->snapshot();

  // attempt parsing the incoming elements now
  auto properties = s_enclosed.dispatch(parser);
  if (!properties.has_value()) return nullptr;

  // construct the resulting list to be used
  return parser->allocate<Syntax::Interface>(snapshot.bounds(), *properties);
}
