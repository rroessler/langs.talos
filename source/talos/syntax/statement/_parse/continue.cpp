/// Syntax Includes
#include "talos/syntax/_inline/statement.ipp"

//  PRIVATE METHODS  //

TALOS_MM_PARSE_STMT(Continue, parser) {
  auto *token = m_assert(parser->advance(), Lexer::Kind::FLOW_CONT);
  return parser->allocate<Syntax::Continue>(Syntax::Bounds(token));
}
