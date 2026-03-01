#ifndef _FORGE_FORMAT_EMPTY_HPP
#define _FORGE_FORMAT_EMPTY_HPP

/// Format Modules
#include "forge/format/nodes/unicode.hpp"

namespace Forge::Format {

    /// @brief Explicit Empty Node.
    struct Node::Empty : public Node::Abstract<Empty, Unicode> {
        //  CONSTRUCTORS  //

        /// @brief A node that is always empty.
        explicit Empty() = default;
    };

}  // namespace Forge::Format

#endif