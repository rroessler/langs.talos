#ifndef _FORGE_FORMAT_SPACE_HPP
#define _FORGE_FORMAT_SPACE_HPP

/// Forge Includes
#include "forge/format/abstract.hpp"

namespace Forge::Format {

    /// @brief Explicit Space Node.
    class Node::Space : public Node::Abstract<Space> {
        //  PROPERTIES  //

        /// @brief Denotes the break state.
        Break m_state;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs the space.
         * @param state             Space state.
         */
        explicit Space(Break state) : m_state(state) {}

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
                case Break::HARD: os << "' '"; break;
                case Break::SOFT: os << "ifBreak(' ', { negate: true })"; break;

                // ignore if the state was invalid here
                default: $_ABORT("Unknown space-break found");
            }
        }
    };

}  // namespace Forge::Format

#endif
