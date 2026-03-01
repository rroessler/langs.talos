/// Forge Modules
#include "forge/format/dispatch.hpp"

/// Syntax Modules
#include "forge/syntax/_inline/expression.ipp"

//  PRIVATE METHODS  //

Forge::Format::Node* Forge::Format::Dispatch::m_identifier(Reader* reader) {
    if (!reader->match(Lexer::Flag::ANNOTATION)) return nullptr;
    return reader->storage()->unicode(reader->previous()->lexeme());
}

FORGE_MM_FORMAT_PREFIX(Identifier, reader) { return m_assignment(reader, m_identifier(reader)); }
