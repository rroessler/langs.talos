/// Talos Includes
#include "talos/format/writer.hpp"

/// Format Includes
#include "talos/format/_inline/pieces.ipp"

//  PRIVATE METHODS  //

size_t Talos::Format::Piece::List::m_width(const Wrap::List &wrapped, bool force) const noexcept {
  return m_apply(m_pieces, wrapped, force);
}

void Talos::Format::Piece::List::m_render(Writer *writer, Wrap wrapping) const noexcept {
  for (const auto &piece : m_pieces) piece->render(writer, wrapping);
}
