/// Forge Modules
#include "forge/format/writer.hpp"

/// Format Nodes
#include "forge/format/_inline/nodes.ipp"

//  PRIVATE METHODS  //

void Forge::Format::Node::Indent::m_render(Writer* writer, Wrap wrapping) const noexcept {
    // ensure we increment the indentation
    auto marker = writer->indent();

    // write all the nodes as necessary now
    for (const auto* node : nodes()) node->render(writer, wrapping);

    // and decrement the final indentation on completion
    writer->dedent(marker);
}
