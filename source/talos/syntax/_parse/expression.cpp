/// Syntax Includes
#include "talos/syntax/_inline/expression.ipp"
#include "talos/syntax/_inline/generator.ipp"

//  PRIVATE METHODS  //

Talos::Syntax::Expression *Talos::Parser::Dispatch::m_expression(Stream *parser, Precedence rank) {
  static constexpr auto s_bail = [](Stream *parser, auto... args) { return parser->report(args...); };
  return Syntax::Generator::expression<Syntax::Expression, Stream, Dispatch>(parser, rank, s_bail);
}
