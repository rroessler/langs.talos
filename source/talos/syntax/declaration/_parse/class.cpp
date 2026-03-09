/// Talos Modules
#include "talos/parser/delimited.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"
#include "talos/syntax/annotation/generics.hpp"

//  PRIVATE METHODS  //

Talos::Syntax::Specialization Talos::Parser::Dispatch::m_implements(Stream* parser) {
    // prepare the output specialization implements
    auto implements = Syntax::Specialization();

    // if there is no implementation keyword, then ignore finding
    if (!parser->match(Lexer::Kind::DECL_IMPLEMENTS)) return implements;

    // if we have an immediate opening brace, then declare a warning
    if (parser->check(Lexer::Kind::PUNC_LBRACE)) return parser->report(2000300), implements;

    // attempt matching annotations whilst possible to do so
    do { implements.emplace_back(m_annotation(parser)); } while (parser->match(Lexer::Kind::PUNC_COMMA));

    // filter and ensure we return the resulting implementation values
    return std::erase_if(implements, [](auto* _) { return _ == nullptr; }), implements;
}

TALOS_MM_PARSE_DECL(Class, parser) {
    // prepare the parser snapshot
    auto snapshot = parser->snapshot();

    // ensure we have a leading class token
    m_assert(parser->advance(), Lexer::Kind::DECL_CLASS);

    // build the necessary identifier to be used now
    auto* name = m_label(parser);
    if (name == nullptr) return nullptr;

    // attempt reading a constructor value to be used
    auto* constructor = m_annotation<Syntax::Constructor>(parser);
    if (constructor == nullptr) return nullptr;  // failed to read

    auto extends = parser->match(Lexer::Kind::ARROW_BOLD);
    auto* super = extends ? m_expression(parser) : nullptr;
    if (super == nullptr && extends) return nullptr;

    // parse the implementation interfaces
    auto implements = m_implements(parser);

    // prepare the details for reading fields
    static constexpr auto s_opening = Lexer::Kind::PUNC_LBRACE;
    static constexpr auto s_closing = Lexer::Kind::PUNC_RBRACE;
    static constexpr auto s_separator = Lexer::Kind::PUNC_TERM;
    static constexpr auto s_callback = [](auto* _) -> Syntax::Declaration* {
        // resolve the baseline field instance
        auto* field = m_preamble(_, Extent::CLASS);
        if (field == nullptr) return nullptr;

        // get the underlying modifiers to be updated
        auto& modifiers = field->modifiers();

        // ignore modifiers that are already defined
        if (modifiers.test(Variable::Flag::PUBLIC, Variable::Flag::PROTECTED)) return field;

        // ensure we default the "private" accessibility flag
        return modifiers.set(Variable::Flag::PRIVATE), field;
    };

    // construct the enclosed handler to bs used now
    static auto s_enclosed = Enclosed<Syntax::Declaration, s_opening, s_closing, s_separator>(s_callback);

    // attempt reading the available fields now
    auto fields = s_enclosed.dispatch(parser);
    if (!fields.has_value()) return nullptr;

    // construct a block to emplace these fields into
    auto* block = parser->allocate<Syntax::Block>(*fields);

    // build the resulting location
    auto location = snapshot.enclose(name);

    // and finally construct the resulting class instance
    return parser->allocate<Syntax::Class>(name->lexeme(), constructor, super, implements, *fields, block, location);
}
