/// Syntax Includes
#include "talos/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

TALOS_MM_PARSE_PREFIX(Text, parser, ) {
  auto *token = m_assert(parser->advance(), Lexer::Kind::LTRL_STR);
  return parser->allocate<Syntax::Text>(Syntax::Bounds(token), token);
}
