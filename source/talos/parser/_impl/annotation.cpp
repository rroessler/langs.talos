/// Syntax Modules
#include "talos/syntax/_inline/annotation.ipp"

//  PRIVATE METHODS  //

Talos::Syntax::Annotation* Talos::Parser::Dispatch::m_annotation(Stream* parser) {
    // get the current token value to be handled now
    auto current = parser->current();

    // switch based on the incoming instance now
    switch (current->kind()) {
        // handle special cases that could be possible
        case Lexer::Kind::DECL_FUNC: return m_annotation<Syntax::Signature>(parser);
        case Lexer::Kind::PUNC_LBRACE: return m_annotation<Syntax::Interface>(parser);

        // fall-throughs are handled differently as necessary
        default: break;
    }

    if (current->flags().test(Lexer::Flag::ANNOTATION)) return m_annotation<Syntax::Qualifier>(parser);
    return parser->report(current, 2000100, "a type-annotation");  // otherwise fail now since no-match
}
