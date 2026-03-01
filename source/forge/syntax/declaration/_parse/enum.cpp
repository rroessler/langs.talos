/// Parser Modules
#include "forge/parser/delimited.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/declaration.ipp"

//  PRIVATE METHODS  //

FORGE_MM_PARSE_DECL(Variant, parser) {
    // prepare the snapshot value
    auto snapshot = parser->snapshot();

    // always expect an initial identifier value now
    auto* key = m_label(parser);
    if (key == nullptr) return nullptr;

    // prepare the suitable label value to be used
    Syntax::Expression* label = nullptr;

    // check for potential label declarations
    if (parser->match(Lexer::Kind::PUNC_LPAREN)) {
        if ((label = m_expression(parser)) == nullptr) return nullptr;  // attempt eating
        if (!parser->expect(Lexer::Kind::PUNC_RPAREN, "an enum label")) return nullptr;
    }

    // attempt matching a suitable expression for the value
    auto initializer = parser->match(Lexer::Kind::ASOP_DEF);
    auto* value = initializer ? m_expression(parser) : nullptr;
    if (value == nullptr && initializer) return nullptr;

    // and construct the resulting member to be used
    return parser->allocate<Syntax::Variant>(key, label, value, snapshot.enclose(key));
}

FORGE_MM_PARSE_DECL(Enum, parser) {
    // prepare the parser snapshot
    auto snapshot = parser->snapshot();

    // ensure we have an incoming identifier now
    m_assert(parser->advance(), Lexer::Kind::DECL_ENUM);

    // attempt parsing the incoming identifier to be used
    auto* name = m_label(parser);
    if (name == nullptr) return nullptr;

    // prepare the details for parsing enum members
    static constexpr auto s_opening = Lexer::Kind::PUNC_LBRACE;
    static constexpr auto s_closing = Lexer::Kind::PUNC_RBRACE;
    static constexpr auto s_callback = m_declaration<Syntax::Variant>;
    static auto s_enclosed = Enclosed<Syntax::Variant, s_opening, s_closing>(s_callback);

    auto cases = s_enclosed.dispatch(parser);
    if (!cases.has_value()) return nullptr;

    // and construct the resulting enumeration now
    return parser->allocate<Syntax::Enum>(name, *cases, snapshot.enclose(name));
}
