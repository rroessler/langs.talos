/// Talos Modules
#include "talos/format/dispatch.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/annotation.ipp"

//  PRIVATE METHODS  //

Talos::Format::Node* Talos::Format::Dispatch::m_template(Reader* reader) {
    // prepare the underlying storage instance
    auto* storage = reader->storage();

    // stop early when possible to do so
    if (!reader->match(Lexer::Kind::PUNC_LBRACK)) return storage->empty();

    // attempt parsing out the collection required now
    auto callback = [](Reader* reader) { return m_annotation<Syntax::Placeholder>(reader); };
    auto* placeholders = m_delimited(reader, { std::move(callback), Lexer::Kind::PUNC_RBRACK });
    if (placeholders == nullptr || !reader->match(Lexer::Kind::PUNC_RBRACK)) return nullptr;

    // prepare the necessary indentation now
    placeholders = storage->indent(storage->line().soft(), placeholders);

    // and construct the resulting group to be returned now
    return storage->group(storage->brack().left(), placeholders, storage->line().soft(), storage->brack().right());
}

TALOS_MM_FORMAT_HINT(Placeholder, reader) {
    // parse an appropriate identifier now
    auto* placeholder = m_identifier(reader);
    if (placeholder == nullptr) return nullptr;

    // prepare the storage to be used
    auto* storage = reader->storage();

    // prepare a suitable callback for annotations
    auto callback = [](Reader* reader) { return m_annotation(reader); };

    // append potential extension hints if given
    auto colon = reader->match(Lexer::Kind::PUNC_COLON);
    auto* extends = colon ? m_leading(reader, Callback(callback)) : nullptr;

    if (extends) placeholder = storage->append(placeholder, storage->colon(), storage->space().hard(), extends);
    else if (colon) return nullptr;  // failed to parse the incoming extension typing so we fail here now

    // append potential fallback types if given
    auto declare = reader->match(Lexer::Kind::ASOP_DEF);
    auto* fallback = declare ? m_leading(reader, Callback(callback)) : nullptr;

    if (fallback) placeholder = storage->append(placeholder, storage->assign(), storage->space().hard(), extends);
    else if (declare) return nullptr;  // failed to parse the incoming fallback typing so we fail here now

    // and return the resulting placeholder now
    return placeholder;
}
