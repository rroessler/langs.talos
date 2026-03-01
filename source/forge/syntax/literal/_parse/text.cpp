/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

FORGE_MM_PARSE_PREFIX(Text, parser, ) {
    auto* token = m_assert(parser->advance(), Lexer::Kind::LTRL_STR);
    return parser->allocate<Syntax::Text>(token);  // fully validated
}
