/// Talos Includes
#include "talos/format/writer.hpp"

/// Format Includes
#include "talos/format/_inline/pieces.ipp"

//  PRIVATE METHODS  //

void Talos::Format::Piece::Indent::m_render(Writer *writer, Wrap wrapping) const noexcept {
  // ensure we increment the indentation
  auto marker = writer->indent();

  // write all the nodes as necessary now
  for (const auto *piece : pieces()) piece->render(writer, wrapping);

  // and decrement the final indentation on completion
  writer->dedent(marker);
}
