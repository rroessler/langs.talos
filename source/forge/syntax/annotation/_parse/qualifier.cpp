/// Forge Modules
#include "forge/parser/delimited.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/annotation.ipp"

//  PRIVATE METHODS  //

Forge::Syntax::Annotation* Forge::Parser::Dispatch::m_qualifier(Stream* parser, const $::String::View& name) {
    auto* identifier = parser->allocate<Syntax::Identifier>(name);
    return parser->allocate<Syntax::Qualifier>(identifier);
}

FORGE_MM_PARSE_HINT(Qualifier, parser) {
    // prepare the underlying delimited/enclosed handlers
    static constexpr auto s_opening = Lexer::Kind::PUNC_LBRACK;
    static constexpr auto s_closing = Lexer::Kind::PUNC_RBRACK;
    static constexpr auto s_separator = Lexer::Kind::PUNC_PERIOD;
    static constexpr auto s_callback = [](auto* _) { return m_annotation(_); };
    static auto s_delimited = Delimited<Syntax::Identifier, s_separator>(m_identifier);
    static auto s_enclosed = Enclosed<Syntax::Annotation, s_opening, s_closing>(s_callback);

    // cache the current range value to be used
    auto snapshot = parser->snapshot();

    // attempt parsing all the available segments now
    auto segments = s_delimited.dispatch(parser);
    if (!segments.has_value()) return nullptr;

    // stop early if there are no types expected
    if (!parser->check(s_opening)) return parser->allocate<Syntax::Qualifier>(*segments, snapshot);

    // attempt getting a generic list now as necessary
    auto types = s_enclosed.dispatch(parser);
    if (!types.has_value()) return nullptr;

    // report a failure if the types are empty at all
    if (types->empty()) parser->report(snapshot, 2000301);

    // construct the resulting end type now
    return parser->allocate<Syntax::Qualifier>(*segments, *types, snapshot);
}
