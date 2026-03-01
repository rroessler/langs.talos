#ifndef _FORGE_FORMAT_UNICODE_HPP
#define _FORGE_FORMAT_UNICODE_HPP

/// Forge Includes
#include "forge/format/abstract.hpp"

namespace Forge::Format {

    /// @brief Explicit Text Node.
    class Node::Unicode : public Node::Abstract<Unicode> {
        //  PROPERTIES  //

        /// @brief Denotes if should be quoted.
        bool m_quoted;

        /// @brief Associated text buffer.
        $::String::Buffer m_buffer;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a text node.
         * @param buffer                Text buffer.
         * @param quoted                Quoted state.
         */
        explicit Unicode(const $::String::View& buffer = "", bool quoted = false) :
            m_quoted(quoted), m_buffer(buffer) {}

        //  PUBLIC METHODS  //

        inline constexpr bool quoted() const { return m_quoted; }
        inline constexpr $::String::View buffer() const { return m_buffer; }

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
        inline void m_print($::Stream::Output& os) const final {
            os << '"' << (m_quoted ? "'" : "") << m_buffer << (m_quoted ? "'" : "") << '"';
        }
    };

}  // namespace Forge::Format

#endif