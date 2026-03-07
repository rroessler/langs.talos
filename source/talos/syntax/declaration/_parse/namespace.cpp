/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PRIVATE METHODS  //

TALOS_MM_PARSE_DECL(Namespace, parser) {
    // prepare the snapshot
    auto snapshot = parser->snapshot();

    // ensure there is an underlying type declaration
    m_assert(parser->advance(), Lexer::Kind::DECL_SPACE);

    // ensure we have a valid name to be used
    auto* name = m_label(parser);
    if (name == nullptr) return nullptr;

    // parse an expected block for the namespace
    auto* block = m_block(parser, true);
    if (block == nullptr) return nullptr;

    // and return the resulting namespace now
    return parser->allocate<Syntax::Namespace>(name->lexeme(), block, snapshot.enclose(name));
}
