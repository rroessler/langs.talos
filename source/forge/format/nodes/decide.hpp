#ifndef _FORGE_FORMAT_DECIDE_HPP
#define _FORGE_FORMAT_DECIDE_HPP

/// Forge Modules
#include "forge/format/abstract.hpp"

namespace Forge::Format {

    /// @brief Explicit Decision Node.
    class Node::Decide : public Node::Abstract<Decide> {
        //  PROPERTIES  //

        /// @brief Bound group sigil.
        Sigil m_group;

        /// @brief Consequence node.
        Node* m_consequence;

        /// @brief Alternative node.
        Node* m_alternative;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an anonmyous decision node.
         * @param consequence       Consequence node.
         * @param alternative       Alternative node.
         */
        explicit Decide(Node* consequence, Node* alternative = nullptr) : Decide(SIZE_MAX, consequence, alternative) {}

        /**
         * @brief Constructs a decision node.
         * @param group             Group sigil.
         * @param consequence       Consequence node.
         * @param alternative       Alternative node.
         */
        explicit Decide(Sigil group, Node* consequence, Node* alternative = nullptr) :
            m_group(group), m_consequence(consequence), m_alternative(alternative) {}

        //  PUBLIC METHODS  //

        inline constexpr Sigil group() const noexcept { return m_group; }
        inline constexpr Node* consequence() const noexcept { return m_consequence; }
        inline constexpr Node* alternative() const noexcept { return m_alternative; }

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
            os << "ifBreak(" << *m_consequence << ", ";
            if (m_alternative) os << *m_alternative;
            else os << "undefined";  // insert empty
            if (m_group == SIZE_MAX) os << ')';
            else os << ", { groupId: " << m_group << " })";
        }
    };

}  // namespace Forge::Format

#endif