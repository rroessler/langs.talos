/// Talos Modules
#include "talos/format/writer.hpp"

/// Format Nodes
#include "talos/format/_inline/nodes.ipp"

//  PRIVATE METHODS  //

size_t Talos::Format::Node::Expand::m_width(const Wrap::List&, bool) const noexcept { return SIZE_MAX; }
void Talos::Format::Node::Expand::m_render(Writer*, Wrap) const noexcept {}
