#ifndef _FORGE_SYNTAX_NODE_HPP
#define _FORGE_SYNTAX_NODE_HPP

/// Forge Modules
#include "forge/lexer/token.hpp"
#include "forge/syntax/bounds.hpp"
#include "forge/type/lattice.hpp"
#include "forge/value/void.hpp"

//  X-MACROS  //

#define XX_SYNTAX_BASES(X) \
    X(Annotation)          \
    X(Expression)          \
    X(Statement)

//  NAMESPACES  //

namespace Forge::Syntax {

    /// @brief Explicit Syntax Traits.
    class Traits {
        //  PROPERTIES  //

        /// @brief Bounds resource location.
        Bounds m_location = {};

        /// @brief Resultant type from analysis.
        Type::Erased m_type = nullptr;

        /// @brief Underlying node tag.
        $::RTTI::Tag m_tag = $::RTTI::Hash();

       public:
        //  CONSTRUCTORS  //

        /// @brief Allow default construction.
        explicit Traits() = default;

        /**
         * @brief Constructs node metadata.
         * @param tag                   Optional tag.
         * @param location              Resource location.
         */
        explicit Traits($::RTTI::Tag tag, const Bounds& location = {}) : m_location(location), m_tag(tag) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying metadata tag.
        inline constexpr $::RTTI::Tag tag() const noexcept { return m_tag; }

        /// @brief Denotes if a node was synthetically created.
        inline constexpr bool synthetic() const noexcept { return m_location.anonymous(); }

        /// @brief Gets the nodes resource.
        inline constexpr $::URI::View resource() const noexcept { return m_location.resource(); }

        /// @brief Gets the underlying bounds location.
        inline constexpr const Bounds& location() const noexcept { return m_location; }

        /// @brief Gets the underlying range and bounds.
        inline constexpr const XLSP::Range& range() const noexcept { return m_location.range(); }
        inline constexpr const XLSP::Range& bounds() const noexcept { return m_location.bounds(); }

        /// @brief Gets the underlying node typing resolved.
        inline constexpr Type::Erased& type() noexcept { return m_type; }
        inline constexpr const Type::Erased& type() const noexcept { return m_type; }

        /// @brief Resolves a compile-time type-lattice.
        inline constexpr Type::Lattice lattice() const noexcept { return Type::Lattice(m_type); }
    };

    /// @brief AST Node Abstraction.
    class $_ABSTRACT Node : public $::RTTI::Dynamic {
        //  PROPERTIES  //

        /// @brief Internal metadata.
        $::Ptr::Unique<Traits> m_traits;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a node instance.
         * @param tag                   Optional tag.
         * @param location              Resource location.
         */
        explicit Node($::RTTI::Tag tag, const Lexer::Token* token) : Node(tag, token->location()) {}
        explicit Node($::RTTI::Tag tag, const Bounds& location = {}) :
            m_traits($::New().unique<Traits>(tag, location)) {}

        /// @brief Virtual abstract destructor.
        virtual ~Node() = default;

        //  PUBLIC METHODS  //

        /// @brief Allow folding values into themselves.
        inline constexpr Value::Any fold() const noexcept { return m_fold(); }

        /// @brief Gets the underlying metadata.
        inline constexpr Traits* traits() const noexcept { return m_traits.get(); }

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

       protected:
        //  PRIVATE METHODS  //

        /// @brief Allows folding values into themselves.
        virtual inline Value::Any m_fold() const noexcept { return Value::Failure(); }
    };

#define X(N, ...) struct N;
    XX_SYNTAX_BASES(X)
#undef X

#define X(N, ...) || std::same_as<T, N>
    template <class T>
    concept Base = std::derived_from<T, Node> XX_SYNTAX_BASES(X);
#undef X

    /// @brief Prepare an internal passthrough template.
    template <class T, Base B = Node>
    using Passthrough = $::RTTI::Extends<T, B>;

    /// @brief Allows extension of nodes.
    template <class T, Base B = Node>
    struct $_ABSTRACT Abstract : public $::RTTI::Extends<T, B> {
        //  CONSTRUCTORS  //

        /**
         * @brief Handles forwarding construction.
         * @param args                  Arguments to forward.
         */
        template <class... As>
        explicit Abstract(As&&... args) : $::RTTI::Extends<T, B>($::RTTI::Hash<T>(), std::forward<As>(args)...) {}
    };

#define X(N, ...)                                                                             \
    struct $_ABSTRACT N : public Passthrough<N> {                                             \
        /**  CONSTRUCTORS  */                                                                 \
                                                                                              \
        using Passthrough<N>::Passthrough;                                                    \
                                                                                              \
       protected:                                                                             \
        /**  PRIVATE METHODS  */                                                              \
                                                                                              \
        $_INLINE_PERF virtual constexpr bool m_is($::RTTI::Tag tag) const noexcept override { \
            return tag == $::RTTI::Hash<N>();                                                 \
        }                                                                                     \
    };

    XX_SYNTAX_BASES(X)
#undef X

}  // namespace Forge::Syntax

//  UNDEFINES  //

#undef XX_SYNTAX_BASES

#endif