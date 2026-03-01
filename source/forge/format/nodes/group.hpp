#ifndef _FORGE_FORMAT_GROUP_HPP
#define _FORGE_FORMAT_GROUP_HPP

/// Format Modules
#include "forge/format/nodes/list.hpp"

namespace Forge::Format {

    /// @brief Explicit Group Node.
    class Node::Group : public Node::Abstract<Group, List> {
        //  PROPERTIES  //

        /// @brief The associated group sigil.
        Sigil m_sigil = 0;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a baseline group.
         * @param sigil                 Sigil to bind.
         * @param nodes                 Group nodes.
         */
        explicit Group(Sigil sigil, const Buffer& nodes = {}) : Abstract(nodes), m_sigil(sigil) {}

        /**
         * @brief Constructs a baseline group.
         * @param sigil                 Sigil to bind.
         * @param capacity              Initial capacity.
         */
        explicit Group(Sigil sigil, size_t capacity) : Abstract(capacity), m_sigil(sigil) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying group sigil.
        inline constexpr Sigil sigil() const noexcept { return m_sigil; }

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
            os << "group([" << $::Convert::join(nodes()) << "], { id: " << m_sigil << " })";
        }
    };

}  // namespace Forge::Format

#endif