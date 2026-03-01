/// Forge Modules
#include "forge/parser/delimited.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/annotation.ipp"

//  PRIVATE METHODS  //

Forge::Syntax::Constructor* Forge::Parser::Dispatch::m_constructor(Stream* parser, bool annotated) {
    // attempt parsing the generics available
    auto generics = m_template(parser);
    if (!generics.has_value()) return nullptr;

    // attempt parsing the available parameters now to be used
    auto* parameters = m_parameters(parser, annotated);
    if (parameters == nullptr) return nullptr;

    // construct the resulting prototype to now be used
    return parser->allocate<Syntax::Constructor>(*generics, parameters);
}

FORGE_MM_PARSE_HINT(Constructor, parser) { return m_constructor(parser, true); }
FORGE_MM_PARSE_DECL(Constructor, parser) { return m_constructor(parser, false); }
