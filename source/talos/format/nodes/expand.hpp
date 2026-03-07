#ifndef _TALOS_FORMAT_EXPAND_HPP
#define _TALOS_FORMAT_EXPAND_HPP

/// Format Modules
#include "talos/format/abstract.hpp"

namespace Talos::Format {

    /// @brief Explicit Empty Node.
    struct Node::Expand : public Node::Abstract<Expand> {
        //  CONSTRUCTORS  //

        /// @brief Forces parent to expand/break.
        explicit Expand() = default;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles writing a node.
         * @param writer                Format writer.
         * @param wrapping              Current wrapping.
         */
        void m_render(Writer* writer, Wrap wrapping) const noexcept final;

        /**
         * @brief Gets the width of a node.
         * @param wrapped               Wrapped groups.
         * @param force                 Forced width flag.
         */
        size_t m_width(const Wrap::List& wrapped, bool force) const noexcept final;

        /**
         * @brief Handles printing format nodes for debug.
         * @param os                    Output stream.
         */
        inline void m_print($::Stream::Output& os) const final { os << "breakParent"; }
    };

}  // namespace Talos::Format

#endif