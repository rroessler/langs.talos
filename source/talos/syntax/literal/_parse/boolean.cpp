/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

TALOS_MM_PARSE_PREFIX(True, parser, ) {
    auto* token = m_assert(parser->advance(), Lexer::Kind::LTRL_TRUE);
    return parser->allocate<Syntax::True>(token);  // validated here
}

TALOS_MM_PARSE_PREFIX(False, parser, ) {
    auto* token = m_assert(parser->advance(), Lexer::Kind::LTRL_FALSE);
    return parser->allocate<Syntax::False>(token);  // validated here
}
