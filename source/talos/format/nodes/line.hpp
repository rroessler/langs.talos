#ifndef _TALOS_FORMAT_LINE_HPP
#define _TALOS_FORMAT_LINE_HPP

/// Talos Includes
#include "talos/format/abstract.hpp"

namespace Talos::Format {

    /// @brief Explicit Line Node.
    class Node::Line : public Node::Abstract<Line> {
        //  PROPERTIES  //

        /// @brief Denotes the break state.
        Break m_state;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs the line.
         * @param state             Line state.
         */
        explicit Line(Break state) : m_state(state) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying break-state.
        inline constexpr Break state() const noexcept { return m_state; }

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
            switch (m_state) {
                case Break::SOFT: os << "softline"; break;
                case Break::HARD: os << "hardline"; break;
                case Break::DYNAMIC: os << "line"; break;
                case Break::LITERAL: os << "literalline"; break;

                // ignore if the state was invalid here
                default: $_ABORT("Unknown line-break found");
            }
        }
    };

}  // namespace Talos::Format

#endif
