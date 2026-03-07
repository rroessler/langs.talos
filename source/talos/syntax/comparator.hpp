#ifndef _TALOS_SYNTAX_COMPARATOR_HPP
#define _TALOS_SYNTAX_COMPARATOR_HPP

/// Talos Modules
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

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

}  // namespace Talos::Syntax

#endif
