/// Talos Includes
#include "talos/format/writer.hpp"

/// Format Includes
#include "talos/format/_inline/pieces.ipp"

//  PRIVATE METHODS  //

size_t Talos::Format::Piece::Expand::m_width(const Wrap::List &, bool) const noexcept { return SIZE_MAX; }
void Talos::Format::Piece::Expand::m_render(Writer *, Wrap) const noexcept {}
