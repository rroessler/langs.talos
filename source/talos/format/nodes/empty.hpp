#ifndef _TALOS_FORMAT_EMPTY_HPP
#define _TALOS_FORMAT_EMPTY_HPP

/// Format Modules
#include "talos/format/nodes/unicode.hpp"

namespace Talos::Format {

    /// @brief Explicit Empty Node.
    struct Node::Empty : public Node::Abstract<Empty, Unicode> {
        //  CONSTRUCTORS  //

        /// @brief A node that is always empty.
        explicit Empty() = default;
    };

}  // namespace Talos::Format

#endif