/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

TALOS_MM_PARSE_INFIX(Infer, parser, value, ) {
    // prepare the snapshot now
    auto snapshot = parser->snapshot().offset(value->traits()->bounds());

    // ensure the cast operator is actually available
    m_assert(parser->advance(), Lexer::Kind::BINOP_IS);

    // check for any potential inversions to be used
    auto negate = parser->match(Lexer::Kind::UNOP_NOT);

    // validate the incoming guard to be used
    auto* guard = m_annotation(parser);
    if (guard == nullptr) return nullptr;

    // and construct the resulting guard now
    return parser->allocate<Syntax::Infer>(value, guard, negate, snapshot.enclose(value));
}
