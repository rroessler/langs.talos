/// Parser Modules
#include "talos/parser/delimited.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

TALOS_MM_PARSE_PREFIX(Record, parser, ) {
    // prepare some details for the enclosing parser
    static constexpr auto s_opening = Lexer::Kind::PUNC_LBRACE;
    static constexpr auto s_closing = Lexer::Kind::PUNC_RBRACE;
    static constexpr auto s_callback = [](auto* _) { return m_variable(_, false); };
    static auto s_enclosed = Enclosed<Syntax::Variable, s_opening, s_closing>(s_callback);

    // get the snapshot to be used now
    auto snapshot = parser->snapshot();

    // attempt parsing the incoming elements now
    auto elements = s_enclosed.dispatch(parser);
    if (!elements.has_value()) return nullptr;

    // construct the resulting list to be used
    return parser->allocate<Syntax::Record>(*elements, snapshot);
}
