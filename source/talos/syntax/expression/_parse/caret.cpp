/// Syntax Includes
#include "talos/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

TALOS_MM_PARSE_PREFIX(Caret, parser, ) {
  auto *token = m_assert(parser->advance(), Lexer::Kind::BINOP_XOR);
  return parser->allocate<Syntax::Caret>(Syntax::Bounds(token));
}
