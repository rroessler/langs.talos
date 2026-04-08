#ifndef _TALOS_RELINT_SCOPE_HPP
#define _TALOS_RELINT_SCOPE_HPP

/// Talos Modules
#include "talos/relint/mirror.hpp"

namespace Talos::Relint {

    /// @brief References Scoping.
    class Scope {
        //  TYPEDEFS  //

        /// @brief Allow the base analyzer internal access.
        friend struct Analyzer;

        //  PROPERTIES  //

        /// @brief Previous references scope.
        Scope* m_ancestor = nullptr;

        /// @brief All bound variable definitions.
        $::Record<$::Ptr::Shared<Definition>> m_definitions = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a references scope.
         * @param ancestor          Scope ancestor.
         */
        explicit Scope(Scope* ancestor = nullptr) : m_ancestor(ancestor) {}

        //  PUBLIC METHODS  //

        /// @brief Gets a view of the available definitions.
        inline constexpr auto view() const noexcept { return m_definitions; }

        /**
         * @brief Declares a variable reference.
         * @param name              Name of variable.
         * @param mirror            Mirror to bind.
         */
        inline constexpr bool declare(const $::String::View& name, Mirror* mirror) noexcept {
            auto definition = m_define(name);
            if (definition->variable) return false;
            mirror->definition()->variable = mirror;
            return definition->variable = mirror, true;
        }

        /**
         * @brief Declares an annotation reference.
         * @param name              Name of annotation.
         * @param mirror            Mirror to bind.
         */
        inline constexpr bool annotate(const $::String::View& name, Mirror* mirror) noexcept {
            auto definition = m_define(name);
            if (definition->annotation) return false;
            mirror->definition()->annotation = mirror;
            return definition->annotation = mirror, true;
        }

        /**
         * @brief Resolves a definition reference.
         * @param name              Name of variable.
         */
        inline constexpr $::Ptr::Shared<Definition> resolve(const $::String::View& name) const noexcept {
            auto iter = m_definitions.find(name);
            if (iter != m_definitions.cend()) return iter->second;
            return m_ancestor ? m_ancestor->resolve(name) : Empty;
        }

        /**
         * @brief We allow linking relational references.
         * @param name              Name of definition.
         * @param child             Child mirror to bind.
         */
        inline void relate(const $::String::View& name, Mirror* child) { return relate(child, resolve(name)); }
        inline void relate(Mirror* child, const $::Ptr::Shared<Definition>& parent) {
            capture(child, parent), subtype(child, parent);
        }

        /**
         * @brief We allow linking variable references.
         * @param name              Name of definition.
         * @param child             Child mirror to bind.
         */
        inline void capture(const $::String::View& name, Mirror* child) { return capture(child, resolve(name)); }
        inline void capture(Mirror* child, const $::Ptr::Shared<Definition>& parent) {
            if (!parent || !parent->variable) return;
            parent->variable->references().emplace_back(child);
            child->definition()->variable = parent->variable;
        }

        /**
         * @brief We allow linking annotation references.
         * @param name              Name of definition.
         * @param child             Child mirror to bind.
         */
        inline void subtype(const $::String::View& name, Mirror* child) { return subtype(child, resolve(name)); }
        inline void subtype(Mirror* child, const $::Ptr::Shared<Definition>& parent) {
            if (!parent || !parent->annotation) return;
            parent->annotation->references().emplace_back(child);
            child->definition()->annotation = parent->annotation;
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Declares a reference instance.
         * @param name              Name of variable.
         */
        inline constexpr $::Ptr::Shared<Definition> m_define(const $::String::View& name) noexcept {
            return m_definitions.try_emplace(name, $::New().shared<Definition>()).first->second;
        }
    };

}  // namespace Talos::Relint

#endif
