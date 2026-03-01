/// Syntax Modules
#include "forge/syntax/_inline/declaration.ipp"

//  PRIVATE METHODS  //

Forge::Syntax::Declaration* Forge::Parser::Dispatch::m_subject(Stream* parser, $::Ternary level) {
    // handle immediate declarations (always valid)
    if (parser->check(Lexer::Flag::VARIABLE)) return m_declaration<Syntax::Variable>(parser);
    if (level == false) return parser->report(2000100, "a class field");  // got invalid field

    // otherwise should be a valid approach for types
    switch (parser->current()->kind()) {
        case Lexer::Kind::DECL_ENUM: return m_declaration<Syntax::Enum>(parser);
        case Lexer::Kind::DECL_TYPE: return m_declaration<Syntax::Alias>(parser);
        case Lexer::Kind::DECL_CLASS: return m_declaration<Syntax::Class>(parser);

        // otherwise we break to check for valid namespacing
        default: break;
    }

    // handle namespaces if possible to do so
    if (level == true && parser->check(Lexer::Kind::DECL_SPACE)) return m_declaration<Syntax::Namespace>(parser);
    return parser->report(2000100, level ? "a top-level declaration" : "a class field");  // unexpected value
}

Forge::Syntax::Declaration* Forge::Parser::Dispatch::m_preamble(Stream* parser, $::Ternary level) {
    // prepare the output decorator and attribute containers
    auto attributes = std::vector<Syntax::Attribute*>();
    auto decorators = std::vector<Syntax::Decorator*>();

    // attempt parsing attributes and decorators whilst possible to do so
    while (parser->check(Lexer::Flag::DECORATES)) {
        if (parser->check(Lexer::Kind::PUNC_ATTRIB)) attributes.emplace_back(m_attribute(parser));
        else if (parser->check(Lexer::Kind::PUNC_DECOR)) decorators.emplace_back(m_decorator(parser));
    }

    // check if either sets where incorrect at all
    auto invalid = std::ranges::contains(decorators, nullptr) || std::ranges::contains(attributes, nullptr);

    // attempt parsing all the available modifiers now
    auto* declaration = m_modifiers(parser, level);
    if (invalid || declaration == nullptr) return nullptr;

    // check for valid preamble items now
    auto valid = declaration->is<Syntax::Variable, Syntax::Class>();
    auto* preamble = valid ? static_cast<Syntax::Preamble*>(declaration) : nullptr;

    // should be able to update the declaration now (if a preamble)
    if (preamble == nullptr) parser->report(declaration, 2000901);
    else preamble->decorators() = decorators, preamble->attributes() = attributes;

    // and return the result
    return declaration;
}

Forge::Syntax::Declaration* Forge::Parser::Dispatch::m_modifiers(Stream* parser, $::Ternary level) {
    // prepare the modifiers output to be used
    auto modifiers = Variable::Modifiers();

    // prepare a handler for setting modifiers
    auto emplace = [&](Variable::Flag flag, const $::String::View& name) {
        if (level != false) parser->report(parser->previous(), level ? 2000902 : 2000903, name);
        else if ($_LIKELY(!modifiers.test(flag))) modifiers.set(flag);  // should be the most likely
        else parser->report(parser->previous(), 2000900, name);         // duplicated flags warning
    };

    // attempt matching as many modifiers as possible now
    while (parser->check(Lexer::Flag::MODIFIER)) {
#define FORGE_XX_TOKEN_MODIFIER(K, N, ...) \
    case Lexer::Kind::MOD_##K: parser->advance(), emplace(Variable::Flag::K, N); break;
        switch (parser->current()->kind()) {
#include "forge/lexer/_defines/tokens.def"
            default: break;
        }
    }

    // update our level as necessary now
    if (modifiers.test(Variable::Flag::STATIC)) level = $::Unknown();

    // attempt parsing a suitable subject now
    auto* declaration = m_subject(parser, level);
    if (declaration == nullptr) return nullptr;

    // update the declarations modifiers
    declaration->modifiers() = declaration->modifiers() | modifiers;

    // and return the resulting declaration
    return declaration;
}
