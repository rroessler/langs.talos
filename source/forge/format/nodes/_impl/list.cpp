/// Forge Modules
#include "forge/format/writer.hpp"

/// Format Nodes
#include "forge/format/_inline/nodes.ipp"

//  PRIVATE METHODS  //

size_t Forge::Format::Node::List::m_width(const Wrap::List& wrapped, bool force) const noexcept {
    return m_apply(m_nodes, wrapped, force);
}

void Forge::Format::Node::List::m_render(Writer* writer, Wrap wrapping) const noexcept {
    for (const auto& node : m_nodes) node->render(writer, wrapping);
}
