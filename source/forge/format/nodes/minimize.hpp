#ifndef _FORGE_FORMAT_MINIMIZE_HPP
#define _FORGE_FORMAT_MINIMIZE_HPP

/// Forge Includes
#include "forge/format/abstract.hpp"

namespace Forge::Format {

    /// @brief Explicit Zero-Width Node.
    class Node::Minimize : public Node::Abstract<Minimize> {
        //  PROPERTIES  //

        /// @brief Minimization target.
        Node* m_target = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Compresses a node to zero-width.
        explicit Minimize() = default;

        /**
         * @brief Constructs a minimization node.
         * @param target            Target to minimize.
         */
        explicit Minimize(Node* target) : m_target(target) {}

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
        inline void m_print($::Stream::Output& os) const final { os << ""; }
    };

}  // namespace Forge::Format

#endif