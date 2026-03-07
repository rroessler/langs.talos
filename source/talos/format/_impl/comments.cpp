/// Talos Modules
#include "talos/format/dispatch.hpp"

//  PRIVATE METHODS  //

Talos::Format::Buffer Talos::Format::Dispatch::m_leading(Reader* reader, bool trim) {
    return (reader->skip(), reader->flush(trim));
}

Talos::Format::Node* Talos::Format::Dispatch::m_leading(Reader* reader, Callback&& callback, bool trim) {
    // prepare the leading whitespace
    auto leading = m_leading(reader, trim);

    // attempt parsing the incoming node
    auto* node = callback(reader);
    if (node == nullptr) return nullptr;

    // stop early if the leading comments are empty
    if (leading.empty()) return node;

    // prepare a storage handler now
    auto* storage = reader->storage();
    auto* collection = storage->list();
    auto* delimiter = storage->line().hard();

    // join all the items together now
    for (const auto& comment : leading) storage->append(collection, comment, delimiter);

    // return the resulting item now
    return storage->append(collection, node);
}

Talos::Format::Node* Talos::Format::Dispatch::m_trailing(Reader* reader) { return reader->trailing(); }
Talos::Format::Node* Talos::Format::Dispatch::m_trailing(Reader* reader, Callback&& callback) {
    return m_trailing(reader, callback(reader));
}

Talos::Format::Node* Talos::Format::Dispatch::m_trailing(Reader* reader, Node* node) {
    // ignore if the incoming item is invalid
    if (node == nullptr) return nullptr;

    // get the trailing comment to be used
    auto* trailing = m_trailing(reader);
    if (trailing == nullptr) return node;

    // get the underlying storage instance
    auto* storage = reader->storage();

    // append the comment node now as needed
    return storage->append(node, storage->space().hard(), trailing);
}
