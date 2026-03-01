/// Forge Modules
#include "forge/format/writer.hpp"

/// Format Nodes
#include "forge/format/_inline/nodes.ipp"

//  PRIVATE METHODS  //

size_t Forge::Format::Node::Decide::m_width(const Wrap::List& wrapped, bool force) const noexcept {
    auto wrapping = m_group != SIZE_MAX && wrapped.contains(m_group);
    if (wrapping) return m_consequence->width(wrapped, force);
    return m_alternative ? m_alternative->width(wrapped, force) : 0;
}

void Forge::Format::Node::Decide::m_render(Writer* writer, Wrap wrapping) const noexcept {
    // prepare the condition to be decided between (for anonymous or explicit)
    auto condition = (m_group == SIZE_MAX && wrapping.enabled()) || writer->wrapped().contains(m_group);

    // attempt running our desired condition now
    if (condition) m_consequence->render(writer, Wrap::State::ENABLED);
    else if (m_alternative) m_alternative->render(writer, wrapping);
}
