#ifndef _FORGE_DECLARATION_ALIAS_HPP
#define _FORGE_DECLARATION_ALIAS_HPP

/// Syntax Modules
#include "forge/syntax/annotation/generics.hpp"
#include "forge/syntax/declaration/preamble.hpp"

namespace Forge::Syntax {

    /// @brief Type Declaration Node.
    class Alias : public Abstract<Alias, Declaration> {
        //  PROPERTIES  //

        /// @brief Type annotation value.
        Annotation* m_hint;

        /// @brief Generics template to be used.
        Template m_generics = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a type declaration.
         * @param name                      Target name.
         * @param hint                      Type annotation.
         * @param location                  Resource location.
         */
        explicit Alias(const $::String::View& name, Annotation* hint, const Bounds& location = {}) :
            Abstract(name, location), m_hint(hint) {}

        /**
         * @brief Constructs a type declaration.
         * @param target                    Target name.
         * @param hint                      Type annotation.
         * @param generics                  Template generics.
         */
        explicit Alias(const Lexer::Token* target, Annotation* hint) : Abstract(target), m_hint(hint) {}

        /**
         * @brief Constructs a type declaration.
         * @param name                      Target name.
         * @param hint                      Type annotation.
         * @param generics                  Template generics.
         * @param location                  Resource location.
         */
        explicit Alias(
            const $::String::View& name, Annotation* hint, const Template& generics, const Bounds& location = {}) :
            Abstract(name, location), m_hint(hint), m_generics(generics) {}

        /**
         * @brief Constructs a type declaration.
         * @param target                    Target name.
         * @param hint                      Type annotation.
         * @param generics                  Template generics.
         */
        explicit Alias(const Lexer::Token* target, Annotation* hint, const Template& generics) :
            Abstract(target), m_hint(hint), m_generics(generics) {}

        //  PUBLIC METHODS  //

        inline constexpr Annotation* hint() const noexcept { return m_hint; }
        inline constexpr const Template& generics() const noexcept { return m_generics; }
    };

}  // namespace Forge::Syntax

#endif
