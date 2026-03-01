/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"
#include "forge/syntax/_inline/statement.ipp"

//  PRIVATE METHODS  //

FORGE_MM_PARSE_STMT(Break, parser) {
    $_ASSERT(parser->check(Lexer::Kind::FLOW_BREAK));
    return parser->allocate<Syntax::Break>(parser->advance());
}

FORGE_MM_PARSE_STMT(Continue, parser) {
    $_ASSERT(parser->check(Lexer::Kind::FLOW_CONT));
    return parser->allocate<Syntax::Continue>(parser->advance());
}

FORGE_MM_PARSE_STMT(Return, parser) {
    auto snapshot = parser->snapshot();  // prepare the entire snapshot
    auto* token = m_assert(parser->advance(), Lexer::Kind::FLOW_RETURN);

    auto* value = parser->check(Lexer::Kind::PUNC_TERM) ? parser->allocate<Syntax::Void>() : m_expression(parser);
    return value ? parser->allocate<Syntax::Return>(value, snapshot.enclose(token)) : nullptr;  // build value now
}
