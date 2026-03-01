/// Forge Modules
#include "forge/format/writer.hpp"

/// Format Nodes
#include "forge/format/_inline/nodes.ipp"

//  PRIVATE METHODS  //

size_t Forge::Format::Node::Expand::m_width(const Wrap::List&, bool) const noexcept { return SIZE_MAX; }
void Forge::Format::Node::Expand::m_render(Writer*, Wrap) const noexcept {}
