/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

TALOS_MM_PARSE_PREFIX(Numeric, parser, ) {
    auto* token = m_assert(parser->advance(), Lexer::Flag::NUMERIC);
    return parser->allocate<Syntax::Numeric>(token);  // validated
}
