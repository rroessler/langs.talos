#ifndef _FORGE_FORMAT_INDENT_HPP
#define _FORGE_FORMAT_INDENT_HPP

/// Format Modules
#include "forge/format/nodes/list.hpp"

namespace Forge::Format {

    /// @brief Explicit Indent Node.
    struct Node::Indent : public Node::Abstract<Indent, List> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles writing a node.
         * @param writer                Format writer.
         * @param wrapping              Current wrapping.
         */
        void m_render(Writer* writer, Wrap wrapping) const noexcept final;

        /**
         * @brief Handles printing format nodes for debug.
         * @param os                    Output stream.
         */
        inline void m_print($::Stream::Output& os) const final {
            os << "indent([" << $::Convert::join(nodes()) << "])";
        }
    };

}  // namespace Forge::Format

#endif