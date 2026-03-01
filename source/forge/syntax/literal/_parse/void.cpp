/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

FORGE_MM_PARSE_PREFIX(Void, parser, ) {
    auto* token = m_assert(parser->advance(), Lexer::Kind::LTRL_VOID);
    return parser->allocate<Syntax::Void>(token);  // fully validated
}
