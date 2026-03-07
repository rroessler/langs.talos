/// Talos Modules
#include "talos/format/writer.hpp"

/// Format Nodes
#include "talos/format/_inline/nodes.ipp"

//  PRIVATE METHODS  //

size_t Talos::Format::Node::Unicode::m_width(const Wrap::List&, bool) const noexcept { return m_buffer.size(); }
void Talos::Format::Node::Unicode::m_render(Writer* writer, Wrap) const noexcept {
    if (!m_quoted) writer->concat(m_buffer);
    else writer->concat("\"", m_buffer, "\"");
}
