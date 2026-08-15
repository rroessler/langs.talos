/// Format Includes
#include "talos/format/_inline/macros.ipp"

//  PRIVATE METHODS  //

Talos::Format::Piece *Talos::Format::Dispatch::m_identifier(Reader *reader) {
  if (!reader->match(Lexer::Flag::ANNOTATES)) return nullptr;
  return reader->storage()->unicode(reader->previous()->lexeme());
}

TALOS_MM_FORMAT_PREFIX(Self, reader) { return m_assignment(reader, m_identifier(reader)); }
TALOS_MM_FORMAT_PREFIX(Identifier, reader) { return m_assignment(reader, m_identifier(reader)); }
