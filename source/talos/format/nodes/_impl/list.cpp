/// Talos Modules
#include "talos/format/writer.hpp"

/// Format Nodes
#include "talos/format/_inline/nodes.ipp"

//  PRIVATE METHODS  //

size_t Talos::Format::Node::List::m_width(const Wrap::List& wrapped, bool force) const noexcept {
    return m_apply(m_nodes, wrapped, force);
}

void Talos::Format::Node::List::m_render(Writer* writer, Wrap wrapping) const noexcept {
    for (const auto& node : m_nodes) node->render(writer, wrapping);
}
