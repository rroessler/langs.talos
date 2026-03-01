#ifndef _FORGE_FORMAT_LIST_HPP
#define _FORGE_FORMAT_LIST_HPP

/// Forge Modules
#include "forge/format/abstract.hpp"

namespace Forge::Format {

    /// @brief Explicit List Node.
    class Node::List : public Node::Abstract<List> {
        //  PROPERTIES  //

        /// @brief Associated fill nodes.
        Buffer m_nodes = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a list of nodes.
         * @param nodes                 List nodes.
         */
        explicit List(const Buffer& nodes = {}) : m_nodes(std::move(nodes)) {}

        /**
         * @brief Constructs a list of nodes.
         * @param capacity              Initial capacity.
         */
        explicit List(size_t capacity) { m_nodes.reserve(capacity); }

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying nodes.
        inline constexpr Buffer& nodes() noexcept { return m_nodes; }
        inline constexpr const Buffer& nodes() const noexcept { return m_nodes; }

        /// @brief Denotes if currently empty.
        inline constexpr bool empty() const noexcept { return m_nodes.empty(); }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles writing a node.
         * @param writer                Format writer.
         * @param wrapping              Current wrapping.
         */
        virtual void m_render(Writer* writer, Wrap wrapping) const noexcept override;

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
        virtual inline void m_print($::Stream::Output& os) const override {
            os << '[' << $::Convert::join(m_nodes) << ']';
        }
    };

}  // namespace Forge::Format

#endif