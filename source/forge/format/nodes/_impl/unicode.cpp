/// Forge Modules
#include "forge/format/writer.hpp"

/// Format Nodes
#include "forge/format/_inline/nodes.ipp"

//  PRIVATE METHODS  //

size_t Forge::Format::Node::Unicode::m_width(const Wrap::List&, bool) const noexcept { return m_buffer.size(); }
void Forge::Format::Node::Unicode::m_render(Writer* writer, Wrap) const noexcept {
    if (!m_quoted) writer->concat(m_buffer);
    else writer->concat("\"", m_buffer, "\"");
}
