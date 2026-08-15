/// Talos Includes
#include "talos/format/writer.hpp"

/// Format Includes
#include "talos/format/_inline/pieces.ipp"

//  PRIVATE METHODS  //

size_t Talos::Format::Piece::Space::m_width(const Wrap::List &, bool) const noexcept { return 1; }
void Talos::Format::Piece::Space::m_render(Writer *writer, Wrap wrapping) const noexcept {
  if (m_state == Break::HARD || !wrapping.enabled()) writer->space();
}
