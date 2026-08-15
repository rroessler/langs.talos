/// Talos Includes
#include "talos/format/dispatch.hpp"

//  PRIVATE METHODS  //

Talos::Format::Buffer Talos::Format::Dispatch::m_leading(Reader *reader, bool trim) {
  return (reader->skip(), reader->flush(trim));
}

Talos::Format::Piece *Talos::Format::Dispatch::m_leading(Reader *reader, Callback &&callback, bool trim) {
  // prepare the leading whitespace
  auto leading = m_leading(reader, trim);

  // attempt parsing the incoming piece
  auto *piece = callback(reader);
  if (piece == nullptr) return nullptr;

  // stop early if the leading comments are empty
  if (leading.empty()) return piece;

  // prepare a storage handler now
  auto *storage = reader->storage();
  auto *collection = storage->list();
  auto *delimiter = storage->line().hard;

  // join all the items together now
  for (const auto &comment : leading) storage->append(collection, comment, delimiter);

  // return the resulting item now
  return storage->append(collection, piece);
}

Talos::Format::Piece *Talos::Format::Dispatch::m_trailing(Reader *reader) { return reader->trailing(); }
Talos::Format::Piece *Talos::Format::Dispatch::m_trailing(Reader *reader, Callback &&callback) {
  return m_trailing(reader, callback(reader));
}

Talos::Format::Piece *Talos::Format::Dispatch::m_trailing(Reader *reader, Piece *piece) {
  // ignore if the incoming item is invalid
  if (piece == nullptr) return nullptr;

  // get the trailing comment to be used
  auto *trailing = m_trailing(reader);
  if (trailing == nullptr) return piece;

  // get the underlying storage instance
  auto *storage = reader->storage();

  // append the comment piece now as needed
  return storage->append(piece, storage->space().hard, trailing);
}
