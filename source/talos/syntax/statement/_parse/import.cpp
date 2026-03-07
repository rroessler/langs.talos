/// Talos Modules
#include "talos/parser/delimited.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/statement.ipp"

//  PRIVATE METHODS  //

Talos::Syntax::Node* Talos::Parser::Dispatch::m_import(Stream* parser, bool module) {
    auto* result = m_statement<Syntax::Import>(parser);  // parse now as needed
    return $_LIKELY(module) ? result : parser->report(result, 8000202, "Imports");
}

Talos::Syntax::Node* Talos::Parser::Dispatch::m_export(Stream* parser, bool module) {
    // if we are not within a module context, allow then error-out
    if ($_UNLIKELY(!module)) return parser->report(m_export(parser, true), 8000202, "Exports");

    // eat the current token now for use
    auto* token = m_assert(parser->current(), Lexer::Kind::MOD_EXPORT);

    // check if we have a leading string for module exports
    switch (parser->peek(1)->kind()) {
        case Lexer::Kind::LTRL_STR: return m_statement<Syntax::Import>(parser);
        default: parser->advance(); break;  // should be suitably breakable here
    }

    // otherwise we attempt reading an item with modifiers now
    auto* declaration = m_modifiers(parser, module);
    if (declaration == nullptr) return nullptr;

    // prepare the modifiers to be updated
    auto& modifiers = declaration->modifiers();

    // emplace onto the modifiers now
    if (!modifiers.test(Variable::Flag::EXPORT)) modifiers.set(Variable::Flag::EXPORT);
    else parser->report(token, 2000900, token->lexeme());  // declare as a duplicate now

    // and return the resulting declaration details now
    return declaration;
}

TALOS_MM_PARSE_STMT(Import, parser) {
    // get the current tokens to be used
    auto snapshot = parser->snapshot();

    auto exported = parser->match(Lexer::Kind::MOD_EXPORT);  // prepare context
    if (!exported && !parser->expect(Lexer::Kind::MOD_IMPORT)) return nullptr;

    // attempt parsing the leading path to be used
    if (!parser->consume(Lexer::Kind::LTRL_STR, 2000100, "an import path")) return nullptr;

    // cache the path to be used
    auto* path = parser->previous();

    // if exported and we do not see an "as" token, then we can stop safely
    if (!parser->match(Lexer::Kind::BINOP_AS)) {
        if (!exported) parser->report(2000100, "import patterns");
        return parser->allocate<Syntax::Import>(path, exported, snapshot.enclose(path));
    }

    // if we have a suitable identifier, then stop early
    if (parser->check(Lexer::Flag::ANNOTATION)) {
        auto identifier = parser->allocate<Syntax::Identifier>(parser->advance());
        return parser->allocate<Syntax::Import>(path, identifier, exported, snapshot.enclose(path));
    }

    // prepare some details for parsring patterns
    static constexpr auto s_callback = m_identifier;
    static constexpr auto s_opening = Lexer::Kind::PUNC_LBRACE;
    static constexpr auto s_closing = Lexer::Kind::PUNC_RBRACE;
    static auto s_enclosed = Enclosed<Syntax::Identifier, s_opening, s_closing>(s_callback);

    // ensure the instance was happily parsed
    auto patterns = s_enclosed.dispatch(parser);
    if (!patterns.has_value()) return nullptr;

    // ensure that we have some patterns to actually declare
    if (patterns->empty()) return parser->report(path, 8000200);

    // resolve the final import declaration
    return parser->allocate<Syntax::Import>(path, *patterns, exported, snapshot.enclose(path));
}
