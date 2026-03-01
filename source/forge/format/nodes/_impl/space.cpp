/// Forge Modules
#include "forge/format/writer.hpp"

/// Format Nodes
#include "forge/format/_inline/nodes.ipp"

//  PRIVATE METHODS  //

size_t Forge::Format::Node::Space::m_width(const Wrap::List&, bool) const noexcept { return 1; }
void Forge::Format::Node::Space::m_render(Writer* writer, Wrap wrapping) const noexcept {
    if (m_state == Break::HARD || !wrapping.enabled()) writer->space();
}
