/// Forge Modules
#include "forge/format/dispatch.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PUBLIC METHODS  //

Forge::Format::Node* Forge::Format::Dispatch::m_binary(Reader* reader, Node* left, Callback&& callback) {
    // get the underlying storage instance
    auto* storage = reader->storage();

    // prepare the initial token to be used
    auto token = (reader->skip(), storage->unicode(reader->advance()->lexeme()));

    // attempt eating the right-hand side argument now
    auto* right = m_leading(reader, std::move(callback));
    if (right == nullptr) return nullptr;  // failed to read

    // and construct the resulting output now
    right = storage->group(storage->indent(storage->space().hard(), right));
    return storage->append(left, storage->space().hard(), token, right);
}

FORGE_MM_FORMAT_INFIX(Binary, reader, left) {
    return m_binary(reader, left, [](Reader* reader) { return m_expression(reader); });
}
