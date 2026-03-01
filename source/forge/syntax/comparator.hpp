#ifndef _FORGE_SYNTAX_COMPARATOR_HPP
#define _FORGE_SYNTAX_COMPARATOR_HPP

/// Forge Modules
#include "forge/syntax/node.hpp"

namespace Forge::Syntax {

    /// @brief Ranges Heap Comparator.
    struct Comparator {
        //  CONSTRUCTORS  //

        /// @brief Constructs a comparator function.
        explicit Comparator() = default;

        //  OPERATOR METHODS  //

        /// @brief Compares two nodes for their range position.
        constexpr bool operator()(const Syntax::Node* left, const Syntax::Node* right) const {
            return left->traits()->range() > right->traits()->range();
        }
    };

}  // namespace Forge::Syntax

#endif
