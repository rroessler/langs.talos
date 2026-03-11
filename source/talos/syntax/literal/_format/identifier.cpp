/// Talos Modules
#include "talos/format/dispatch.hpp"

/// Syntax Modules
#include "talos/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

Talos::Format::Node* Talos::Format::Dispatch::m_identifier(Reader* reader) {
    if (!reader->match(Lexer::Flag::ANNOTATION)) return nullptr;
    return reader->storage()->unicode(reader->previous()->lexeme());
}

TALOS_MM_FORMAT_PREFIX(Self, reader) { return m_assignment(reader, m_identifier(reader)); }
TALOS_MM_FORMAT_PREFIX(Identifier, reader) { return m_assignment(reader, m_identifier(reader)); }
