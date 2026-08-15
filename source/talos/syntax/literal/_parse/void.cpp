/// Syntax Includes
#include "talos/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

TALOS_MM_PARSE_PREFIX(Void, parser, ) {
  auto *token = m_assert(parser->advance(), Lexer::Kind::LTRL_VOID);
  return parser->allocate<Syntax::Void>(Syntax::Bounds(token));
}
