#ifndef _FORGE_RELINT_MIRROR_HPP
#define _FORGE_RELINT_MIRROR_HPP

/// Forge Modules
#include "forge/forward/relint.hpp"
#include "forge/syntax/visitor.hpp"

namespace Forge::Relint {

    /// @brief Helper for relinting overloads.
    template <class... Fs>
    struct Overloads : Fs... {
        //  OPERATORS  //

        /// @brief Inherit the base operators.
        using Fs::operator()...;

        //  PUBLIC METHODS  //

        template <class... As>
        static constexpr bool invocable = std::is_invocable<Overloads<Fs...>, As...>();

        template <std::derived_from<Syntax::Node> T>
        static constexpr bool full = invocable<const T*, const Mirror*>;

        template <std::derived_from<Syntax::Node> T>
        static constexpr bool partial = invocable<const T*>;
    };

    /// @brief Encapsulates Reflected Syntax Metadata.
    class Mirror {
        //  PROPERTIES  //

        /// @brief The bound comments to declarations.
        $::String::Buffer m_comments = "";

        /// @brief The associated parent node.
        const Mirror* m_parent = nullptr;

        /// @brief The associated origin node.
        const Syntax::Node* m_origin = nullptr;

        /// @brief The associated type definition.
        const Mirror* m_annotation = nullptr;

        /// @brief The associated declaration definition.
        const Mirror* m_declaration = nullptr;

        /// @brief Currently available references to the origin node.
        std::vector<const Mirror*> m_references = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief An anonymous mirror instance.
        explicit Mirror() = default;

        /**
         * @brief Constructs a syntax mirror.
         * @param origin                Origin node.
         * @param parent                Parent node.
         */
        explicit Mirror(const Syntax::Node* origin, const Mirror* parent = nullptr) :
            m_parent(parent), m_origin(origin) {}

        //  PUBLIC METHODS  //

        /// @brief Parent node of the mirror.
        inline constexpr const Mirror* parent() const noexcept { return m_parent; }

        /// @brief The origin of the mirror.
        inline constexpr const Syntax::Node* origin() const noexcept { return m_origin; }

        /// @brief Gets the underlying typing.
        inline constexpr Type::Erased typing() const noexcept { return m_origin->traits()->type(); }

        /// @brief Gets the associated range/bounds values.
        inline constexpr const XLSP::Range& range() const noexcept { return m_origin->traits()->range(); }
        inline constexpr const XLSP::Range& bounds() const noexcept { return m_origin->traits()->bounds(); }

        /// @brief The bound documentation comments.
        inline constexpr $::String::Buffer& comments() { return m_comments; }
        inline constexpr $::String::View comments() const noexcept { return m_comments; }

        /// @brief Type declaration of the mirror.
        inline constexpr const Mirror*& annotation() noexcept { return m_annotation; }
        inline constexpr const Mirror* annotation() const noexcept { return m_annotation; }

        /// @brief Variable declaration of the node.
        inline constexpr const Mirror*& declaration() noexcept { return m_declaration; }
        inline constexpr const Mirror* declaration() const noexcept { return m_declaration; }

        /// @brief All available references for the node.
        inline constexpr std::vector<const Mirror*>& references() noexcept { return m_references; }
        inline constexpr const std::vector<const Mirror*>& references() const noexcept { return m_references; }

        /// @brief Gets the canonical representation of the node.
        inline constexpr $::String::View canonical() const noexcept {
#define X(N, ...) \
    case $::RTTI::Hash<Syntax::N>(): return #N;
            switch (m_origin->traits()->tag()) { FORGE_XX_SYNTAX_NODES(X) default : return "Unknown"; }
#undef X
        }

        /// @brief Allow conversion to any valid typing.
        template <std::derived_from<Syntax::Node> T>
        inline constexpr const T* when() const noexcept {
            return m_origin->is<T>() ? static_cast<const T*>(m_origin) : nullptr;
        }

        /// @brief Attempts scanning upwards for a parent.
        template <std::derived_from<Syntax::Node> T>
        inline constexpr const T* parent() const noexcept {
            if (m_parent == nullptr) return nullptr;
            if (auto node = m_parent->when<T>()) return node;
            return m_parent->parent<T>();  // scan further
        }

        /// @brief Allows visiting different nodes.
        template <class... Fs>
        inline constexpr auto visit(Overloads<Fs...>&& overloads) const noexcept {
#define X(N, ...)                                                            \
    case $::RTTI::Hash<Syntax::N>(): {                                       \
        if constexpr (Overloads<Fs...>::template full<Syntax::N>)            \
            return overloads(static_cast<const Syntax::N*>(m_origin), this); \
        else if constexpr (Overloads<Fs...>::template partial<Syntax::N>)    \
            return overloads(static_cast<const Syntax::N*>(m_origin));       \
    } break;

            // attempt handling the incoming node instance now
            switch (m_origin->traits()->tag()) { FORGE_XX_SYNTAX_NODES(X) default : break; }
#undef X

            if constexpr (Overloads<Fs...>::template invocable<>) return overloads();
            else if constexpr (Overloads<Fs...>::template invocable<const Mirror*>) return overloads(this);
            else if constexpr (Overloads<Fs...>::template partial<Syntax::Node>) return overloads(m_origin);
            else if constexpr (Overloads<Fs...>::template full<Syntax::Node>) return overloads(m_origin, this);
        }
    };

}  // namespace Forge::Relint

#endif
