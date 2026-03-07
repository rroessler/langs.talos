/// Talos Modules
#include "talos/format/writer.hpp"

/// Format Nodes
#include "talos/format/_inline/nodes.ipp"

//  PRIVATE METHODS  //

void Talos::Format::Node::Indent::m_render(Writer* writer, Wrap wrapping) const noexcept {
    // ensure we increment the indentation
    auto marker = writer->indent();

    // write all the nodes as necessary now
    for (const auto* node : nodes()) node->render(writer, wrapping);

    // and decrement the final indentation on completion
    writer->dedent(marker);
}
