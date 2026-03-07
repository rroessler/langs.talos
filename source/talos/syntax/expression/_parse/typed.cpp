/// Talos Modules
#include "talos/parser/delimited.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

TALOS_MM_PARSE_INFIX(Typed, parser, value, ) {
    // prepare the details to be used to parse a typed expression
    static constexpr auto s_opening = Lexer::Kind::PUNC_LBRACK;
    static constexpr auto s_closing = Lexer::Kind::PUNC_RBRACK;
    static constexpr auto s_callback = [](auto* _) { return m_annotation(_); };
    static auto s_enclosed = Enclosed<Syntax::Annotation, s_opening, s_closing>(s_callback);

    // prepare the typed-arguments snapshot
    auto snapshot = parser->snapshot().offset(value->traits()->bounds());

    // attempt parsing the incoming types now
    auto types = s_enclosed.dispatch(parser);
    if (!types.has_value()) return nullptr;

    // fail if the types are empty at all
    if (types->empty()) parser->report(snapshot, 2000301);

    // and construct the resulting typed expression
    return parser->allocate<Syntax::Typed>(value, *types, snapshot.enclose(value));
}
