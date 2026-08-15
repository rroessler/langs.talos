/// Syntax Includes
#include "talos/syntax/_inline/expression.ipp"
#include "talos/syntax/_inline/statement.ipp"

//  PRIVATE METHODS  //

TALOS_MM_PARSE_STMT(Return, parser) {
  auto snapshot = parser->snapshot(); // prepare the entire snapshot
  auto *token = m_assert(parser->advance(), Lexer::Kind::FLOW_RETURN);

  auto *value = parser->check(Lexer::Kind::PUNC_TERM) ? parser->allocate<Syntax::Void>() : m_expression(parser);
  return value ? parser->allocate<Syntax::Return>(snapshot.enclose(token), value) : nullptr; // build value now
}
