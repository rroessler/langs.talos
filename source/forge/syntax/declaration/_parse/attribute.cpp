/// Syntax Modules
#include "forge/syntax/_inline/declaration.ipp"

//  PRIVATE METHODS  //

Forge::Reflect::Category Forge::Parser::Dispatch::m_category(Stream* parser) {
    // prepare the initial category to be used
    auto category = Reflect::Category::UNKNOWN;

    // attempt getting the category name to validate
    if (!parser->check(Lexer::Flag::ANNOTATION)) return category;

#define X(C, N, ...) \
    case XH::FNV::U32(N): return Reflect::Category::C;
    // and attempt resolving the category name now
    switch (XH::FNV::U32(parser->current()->lexeme())) { FORGE_XX_REFLECTION_CATEGORIES(X) default : break; }
#undef X

    // return the resulting category
    return category;
}

Forge::Syntax::Attribute* Forge::Parser::Dispatch::m_attribute(Stream* parser) {
    // ensure there is the leading token available
    m_assert(parser->advance(), Lexer::Kind::PUNC_ATTRIB);

    // ensure there is a leading bracket as well
    if (!parser->expect(Lexer::Kind::PUNC_LBRACK)) return nullptr;

    // attempt parsing an incoming category to be used
    Syntax::Attribute* attribute = nullptr;

    // attempt parsing based on the incoming category now
    switch (m_category(parser)) {
        case Reflect::Category::OPERATOR: attribute = m_declaration<Syntax::Operator>(parser); break;
        case Reflect::Category::OVERLOAD: attribute = m_declaration<Syntax::Overload>(parser); break;
        case Reflect::Category::DEPRECATED: attribute = m_declaration<Syntax::Deprecated>(parser); break;
        default: return parser->report(2000800, parser->current()->lexeme());
    }

    // attempt checking for a closing bracket now
    if (!parser->expect(Lexer::Kind::PUNC_RBRACK)) return nullptr;

    // return the resulting attribute now
    return attribute;
}

FORGE_MM_PARSE_DECL(Attribute, parser) { return m_attribute(parser); }
