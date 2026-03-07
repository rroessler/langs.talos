/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PRIVATE METHODS  //

Talos::Syntax::Decorator* Talos::Parser::Dispatch::m_decorator(Stream* parser) {
    // prepare the snapshot to be used
    auto snapshot = parser->snapshot();

    // ensure there is the leading token available
    m_assert(parser->advance(), Lexer::Kind::PUNC_DECOR);

    // parse the incoming expression to be used now
    auto* expression = m_expression(parser);
    if (expression == nullptr) return nullptr;

    // should be a valid decorator to construct
    return parser->allocate<Syntax::Decorator>(expression, snapshot.enclose(expression));
}

TALOS_MM_PARSE_DECL(Decorator, parser) { return m_decorator(parser); }
