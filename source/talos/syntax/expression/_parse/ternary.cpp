/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

TALOS_MM_PARSE_INFIX(Ternary, parser, condition, ) {
    // prepare the snapshot now
    auto snapshot = parser->snapshot().offset(condition->traits()->bounds());

    // ensure there is a leading ternary to be used now
    m_assert(parser->advance(), Lexer::Kind::PUNC_QUERY);

    // attempt parsing the consequence
    auto* consequence = m_expression(parser);

    // ensure we have a separator between our values
    if (!parser->expect(Lexer::Kind::PUNC_COLON)) return nullptr;

    // attempt parsing the alternative value now
    auto* alternative = m_expression(parser);

    // ensure our consequence and alternative are valid
    if (consequence == nullptr || alternative == nullptr) return nullptr;

    // construct the resulting ternary now
    return parser->allocate<Syntax::Ternary>(condition, consequence, alternative, snapshot.enclose(condition));
}
