/// Talos Includes
#include "talos/format/dispatch.hpp"

//  PRIVATE METHODS  //

bool Talos::Format::Delimited::m_condition(Reader *) { return false; }

Talos::Format::Piece *Talos::Format::Delimited::m_callback(Reader *reader) { return Dispatch::m_declaration(reader); }

Talos::Format::Delimited::Condition Talos::Format::Delimited::m_closing(Lexer::Kind closing) {
  return [closing](Reader *reader) { return reader->check(closing); };
}