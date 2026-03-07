#ifndef _TALOS_FORMAT_NODE_HPP
#define _TALOS_FORMAT_NODE_HPP

/// Talos Modules
#include "talos/format/wrap.hpp"

//  X-MACROS  //

#define XX_FORMAT_NODES(X) \
    X(Line, class)         \
    X(Space, class)        \
    X(Empty, struct)       \
    X(Unicode, class)      \
    X(Comment, class)      \
                           \
    X(List, class)         \
    X(Group, class)        \
    X(Indent, struct)      \
                           \
    X(When, class)         \
    X(Decide, class)       \
    X(Expand, struct)      \
    X(Minimize, class)

//  NAMESPACES  //

namespace Talos::Format {

    /// @brief Line/Space Break Typing.
    enum class Break : uint8_t {
        SOFT,     // soft break
        HARD,     // hard break
        DYNAMIC,  // dynamic line
        LITERAL,  // literal line
    };

    /// @brief Format Node Base.
    struct Node : public $::Printable, $::RTTI::Dynamic {
        //  TYPEDEFS  //

#define X(N, D, ...) D N;
        XX_FORMAT_NODES(X);
#undef X

        /// @brief Format Node Abstraction.
        template <class T, std::derived_from<Node> B = Node>
        class Abstract : public $::RTTI::Extends<T, B> {
            //  TYPEDEFS  //

#define X(N, ...) using Node::N;
            XX_FORMAT_NODES(X);
#undef X

           public:
            //  CONSTRUCTORS  //

            /// @brief Inherit the base constructor.
            using $::RTTI::Extends<T, B>::Extends;

            //  PUBLIC METHODS  //

            /// @brief Gets the switch-based tag to inherit.
            virtual inline constexpr $::RTTI::Tag tag() const noexcept override { return $::RTTI::Hash<T>(); }
        };

        //  CONSTRUCTORS  //

        /// @brief Defaulted node constructor.
        explicit Node() = default;

        /// @brief Virtual abstract destructor.
        virtual ~Node() = default;

        //  PUBLIC METHODS  //

        /// @brief The internal tag value to expose.
        virtual $::RTTI::Tag tag() const noexcept = 0;

        /// @brief Allows casting to derived values.
        template <std::derived_from<Node> T>
        inline constexpr T* as() noexcept {
            return $::RTTI::Assert<T>(this), static_cast<T*>(this);
        }

        /// @brief Allows casting to derived values.
        template <std::derived_from<Node> T>
        inline constexpr const T* as() const noexcept {
            return $::RTTI::Assert<T>(this), static_cast<const T*>(this);
        }

        /**
         * @brief Gets the width of a node.
         * @param wrapped               Wrapped groups.
         * @param force                 Forced width flag.
         */
        inline constexpr size_t width(const Wrap::List& wrapped = {}, bool force = false) const noexcept {
            return m_width(wrapped, force);
        }

        /**
         * @brief Handles writing a node.
         * @param writer                Format writer.
         * @param wrapping              Current wrapping.
         */
        inline constexpr void render(Writer* writer, Wrap wrapping = Wrap::State::DETECT) const noexcept {
            m_render(writer, wrapping);
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles writing a node.
         * @param writer                Format writer.
         * @param wrapping              Current wrapping.
         */
        virtual void m_render(Writer* writer, Wrap wrapping) const noexcept = 0;

        /**
         * @brief Gets the width of a node.
         * @param wrapped               Wrapped groups.
         * @param force                 Forced width flag.
         */
        virtual size_t m_width(const Wrap::List& wrapped, bool force) const noexcept = 0;

        /**
         * @brief Gets the width of multiple nodes.
         * @param nodes                 Nodes to revise.
         * @param wrapped               Wrapped groups.
         * @param force                 Forced width flag.
         */
        inline constexpr size_t m_apply(const Buffer& nodes, const Wrap::List& wrapped, bool force) const noexcept {
            // prepare the baseline accumulator to be used
            size_t acc = 0;

            // iterate over the available nodes to be used
            for (const auto* node : nodes) {
                acc = std::add_sat(acc, node->width(wrapped, force));
                if (acc == SIZE_MAX) return SIZE_MAX;  // stop early
            }

            // and return the final accumulator now
            return acc;
        }

        /**
         * @brief Handles printing format nodes for debug.
         * @param os                    Output stream.
         * @param self                  Node instance.
         */
        virtual void m_print($::Stream::Output& os) const = 0;
        static inline void m_print($::Stream::Output& os, const Node& self) { self.m_print(os); }
    };

}  // namespace Talos::Format

//  UNDEFINES  //

#undef XX_FORMAT_NODES

#endif
