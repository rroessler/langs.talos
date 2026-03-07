/// Talos Modules
#include "talos/format/dispatch.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PRIVATE METHODS  //

Talos::Format::Node* Talos::Format::Dispatch::m_implements(Reader* reader) {
    // prepare the storage instance
    auto* storage = reader->storage();

    // stop if there is no valid declaration
    if (!reader->match(Lexer::Kind::DECL_IMPLEMENTS)) return storage->empty();

    // prepare the baseline token now
    auto* space = storage->space().hard();
    auto* prefix = storage->unicode(reader->previous()->lexeme());

    // attempt parsing out the collection required now
    auto* implements = m_delimited(reader, { m_identifier, Lexer::Kind::PUNC_LBRACE });

    // bind the "implements" token as well
    return implements ? storage->group(space, prefix, space, implements) : nullptr;
}

TALOS_MM_FORMAT_DECL(Class, reader) {
    // ensure we eat the leading class details
    if (!reader->match(Lexer::Kind::DECL_CLASS)) return nullptr;

    auto* storage = reader->storage();      // prepare the base details
    auto* space = storage->space().hard();  // and the space node to use
    Node* prefix = storage->unicode(reader->previous()->lexeme());

    // attempt getting a suitable identifier
    auto* name = m_identifier(reader);
    if (name == nullptr) return nullptr;

    // prepare the baseline group for the namespace now
    auto* header = storage->group(prefix, space, name);

    // attempt parsing the incoming constructor
    auto* constructor = m_constructor(reader);
    if (constructor == nullptr) return nullptr;

    // append the header now with the incoming constructor
    storage->append(header, constructor);

    // check for a suitable extension typing now
    auto extends = reader->match(Lexer::Kind::ARROW_BOLD);
    auto* super = extends ? m_expression(reader) : nullptr;
    if (super == nullptr && extends) return nullptr;

    // append the extension typing now
    if (super) storage->append(header, space, storage->arrow().bold(), space, super);

    // attempt parsing the implementation interfaces
    auto* implements = m_implements(reader);
    if (implements == nullptr) return nullptr;
    else storage->append(header, implements);

    // attempt parsing the incoming block as well
    auto* block = m_block(reader, header);
    if (block == nullptr) return nullptr;

    // finally cnostruct the end result to be returned
    return storage->group(header, storage->append(block, storage->expand()));
}
