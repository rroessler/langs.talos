/// Talos Modules
#include "talos/format/dispatch.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/declaration.ipp"

//  PRIVATE METHODS  //

TALOS_MM_FORMAT_DECL(Operator, reader) {
    // ensure there is now a period available
    if (!reader->match(Lexer::Kind::PUNC_PERIOD)) return nullptr;

    // attempt getting any incoming operator to be used
    auto* identifier = m_identifier(reader);
    if (identifier == nullptr) return nullptr;

    auto* storage = reader->storage();  // prepare the base
    auto prefix = storage->append(storage->period(), identifier);

    // check if there is a given self value at all
    if (reader->check(Lexer::Kind::PUNC_RBRACK)) return prefix;

    // there could be a valid self-expression now, so parse
    auto* self = m_expression(reader);
    if (self == nullptr) return nullptr;

    // return the resulting output now
    return storage->append(prefix, storage->space().hard(), self);
}
