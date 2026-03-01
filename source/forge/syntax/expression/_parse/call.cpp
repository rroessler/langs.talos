/// Forge Modules
#include "forge/parser/delimited.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

FORGE_MM_PARSE_INFIX(Call, parser, callee, ) {
    // prepare the arguments details to be used
    static constexpr auto s_opening = Lexer::Kind::PUNC_LPAREN;
    static constexpr auto s_closing = Lexer::Kind::PUNC_RPAREN;
    static constexpr auto s_callback = [](auto* _) { return m_expression(_); };
    static auto s_enclosed = Enclosed<Syntax::Expression, s_opening, s_closing>(s_callback);

    // prepare the parser snapshot
    auto snapshot = parser->snapshot().offset(callee->traits()->bounds());

    // attempt getting the available call arguments
    auto arguments = s_enclosed.dispatch(parser);
    if (!arguments.has_value()) return nullptr;

    // and construct the resulting call instance
    return parser->allocate<Syntax::Call>(callee, *arguments, snapshot.enclose(callee));
}
