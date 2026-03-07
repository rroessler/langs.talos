/// Talos Modules
#include "talos/format/dispatch.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PRIVATE METHODS  //

TALOS_MM_FORMAT_DECL(Alias, reader) {
    // eat the leading alias token now
    if (!reader->match(Lexer::Kind::DECL_TYPE)) return nullptr;

    auto* storage = reader->storage();  // prepare the base details
    Node* alias = storage->unicode(reader->previous()->lexeme());

    // attempt getting a suitable identifier
    auto* name = m_identifier(reader);
    if (name == nullptr) return nullptr;

    // attempt parsing any potential generics now
    auto* generics = m_template(reader);
    if (generics == nullptr) return nullptr;

    // build up the alias now
    alias = storage->group(alias, storage->space().hard(), name, generics);

    // ensure we have an assignment now
    return m_assignment(reader, alias, [](Reader* reader) { return m_annotation(reader); });
}
