/// Talos Modules
#include "talos/format/dispatch.hpp"

//  PRIVATE METHODS  //

Talos::Format::Node::List* Talos::Format::Dispatch::m_collection(Reader* reader, Delimited&& delimited) {
    // prepare the outgoing collection
    auto* storage = reader->storage();

    // prepare the collection to be used now
    auto collection = Collection(delimited.separator);

    // iterate whilst we are possibly can
    for (;;) {
        // append all the leading whitespace now here
        for (auto* comment : m_leading(reader, collection.trimmable())) collection.whitespace(comment);

        // check for exit condition potentially
        if (reader->eos() || delimited.exit(reader)) break;

        // prepare the incoming node and trailing items
        auto* node = delimited.consume(reader);
        auto trailing = m_trailing(reader);

        // attempt parsing the incoming item
        if (!collection.append(node, trailing)) return nullptr;
    }

    // return the resulting collection now
    return collection.merge(storage, delimited.trailing);
}

Talos::Format::Node::List* Talos::Format::Dispatch::m_delimited(Reader* reader, Delimited&& delimited) {
    delimited.separator = reader->storage()->comma();
    delimited.trailing = reader->options()->commas_trailing;
    return m_collection(reader, std::move(delimited));
}

Talos::Format::Node* Talos::Format::Dispatch::m_terminates(Reader* reader, Node* node) {
    // if the node is invalid, then immediately propagate
    if (node == nullptr) return nullptr;

    // we check if there is an immediately found terminator
    auto found = reader->current()->kind() == Lexer::Kind::PUNC_TERM ? reader->advance(), true : false;

    // do not force a semicolon if are options allow for it
    if (!found && !reader->options()->terminator_insert) return nullptr;

    // prepare the storage instance to be used
    auto* storage = reader->storage();

    // append the necessary details to the list
    return storage->append(node, storage->terminator());
}
