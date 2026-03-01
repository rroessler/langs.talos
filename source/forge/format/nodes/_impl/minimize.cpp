/// Forge Modules
#include "forge/format/writer.hpp"

/// Format Nodes
#include "forge/format/_inline/nodes.ipp"

//  PRIVATE METHODS  //

size_t Forge::Format::Node::Minimize::m_width(const Wrap::List& wrapped, bool force) const noexcept {
    return force && m_target ? m_target->width(wrapped, force) : 0;
}

void Forge::Format::Node::Minimize::m_render(Writer* writer, Wrap wrapping) const noexcept {
    if (m_target) m_target->render(writer, wrapping);
}
