/// Talos Includes
#include "talos/format/writer.hpp"

/// Format Includes
#include "talos/format/_inline/pieces.ipp"

//  PRIVATE METHODS  //

void Talos::Format::Piece::Group::m_render(Writer *writer, Wrap wrapping) const noexcept {
  // resolve the necessary wrapping to be used
  wrapping = [wrapping, writer, this] {
    if (wrapping.disabled()) return Wrap::State::DISABLED;
    else if (wrapping.forced()) return Wrap::State::ENABLED;
    return writer->exceeds(this) ? Wrap::State::ENABLED : Wrap::State::DETECT;
  }();

  // update our wrapped groups that are available now
  if (wrapping.enabled()) writer->wrapped().emplace(sigil());

  // and attempt updating all our nodes now as well
  for (const auto &piece : pieces()) piece->render(writer, wrapping);
}
