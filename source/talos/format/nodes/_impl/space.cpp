/// Talos Modules
#include "talos/format/writer.hpp"

/// Format Nodes
#include "talos/format/_inline/nodes.ipp"

//  PRIVATE METHODS  //

size_t Talos::Format::Node::Space::m_width(const Wrap::List&, bool) const noexcept { return 1; }
void Talos::Format::Node::Space::m_render(Writer* writer, Wrap wrapping) const noexcept {
    if (m_state == Break::HARD || !wrapping.enabled()) writer->space();
}
