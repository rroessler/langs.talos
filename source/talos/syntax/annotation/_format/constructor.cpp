/// Talos Modules
#include "talos/format/dispatch.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/annotation.ipp"

//  PRIVATE METHODS  //

Talos::Format::Node* Talos::Format::Dispatch::m_constructor(Reader* reader) {
    return m_annotation<Syntax::Constructor>(reader);
}

TALOS_MM_FORMAT_HINT(Constructor, reader) {
    // attempt parsing the generics available
    auto* generics = m_template(reader);
    if (generics == nullptr) return nullptr;

    // attempt parsing the incoming parameters now
    auto* parameters = m_parameters(reader);
    if (parameters == nullptr) return nullptr;

    // prepare the storage instance to be used
    auto* storage = reader->storage();

    // stop early if either are empty now
    if (generics->is<Node::Empty>() && parameters->is<Node::Empty>()) return storage->empty();

    // and construct the resulting constructor to be used now
    return storage->group(generics, parameters);
}
