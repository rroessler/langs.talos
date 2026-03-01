/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

FORGE_MM_PARSE_PREFIX(True, parser, ) {
    auto* token = m_assert(parser->advance(), Lexer::Kind::LTRL_TRUE);
    return parser->allocate<Syntax::True>(token);  // validated here
}

FORGE_MM_PARSE_PREFIX(False, parser, ) {
    auto* token = m_assert(parser->advance(), Lexer::Kind::LTRL_FALSE);
    return parser->allocate<Syntax::False>(token);  // validated here
}
