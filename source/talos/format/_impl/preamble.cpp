/// Talos Modules
#include "talos/format/dispatch.hpp"

//  PRIVATE METHODS  //

Talos::Format::Node* Talos::Format::Dispatch::m_attribute(Reader*) { return nullptr; }
Talos::Format::Node* Talos::Format::Dispatch::m_decorator(Reader*) { return nullptr; }

Talos::Format::Node* Talos::Format::Dispatch::m_preamble(Reader* reader) {
    // prepare the attribute and decorator nodes
    auto attributes = Buffer(), decorators = Buffer();

    // whilst we can match attributes, we parse them as necessary
    while (reader->check(Lexer::Flag::DECORATES)) {
        if (reader->check(Lexer::Kind::PUNC_ATTRIB)) attributes.emplace_back(m_attribute(reader));
        else if (reader->check(Lexer::Kind::PUNC_DECOR)) decorators.emplace_back(m_decorator(reader));
    }

    // check if either are invalid at all (this means we should stop formatting)
    if (std::ranges::contains(attributes, nullptr) || std::ranges::contains(decorators, nullptr)) return nullptr;

    // we now want to attempt parsing our incoming modifiers with leading whitespace
    auto* declaration = m_modifiers(reader);
    if (declaration == nullptr) return nullptr;

    // and finally we merge everything together
    auto* storage = reader->storage();
    auto* preamble = storage->list();

    // prepend the attributes, then the decorators
    for (const auto& attribute : attributes) storage->append(preamble, attribute, storage->line().hard());
    for (const auto& decorator : decorators) storage->append(preamble, decorator, storage->line().hard());

    // finally resolve the declaration to be appended
    return storage->append(preamble, declaration);
}
