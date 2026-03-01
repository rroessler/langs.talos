#ifndef _FORGE_DECLARATION_PREAMBLE_HPP
#define _FORGE_DECLARATION_PREAMBLE_HPP

/// Forge Modules
#include "forge/variable/modifiers.hpp"

/// Syntax Modules
#include "forge/syntax/declaration/attribute.hpp"
#include "forge/syntax/declaration/decorator.hpp"

namespace Forge::Syntax {

    /// @brief Declaration Node Abstractions.
    class $_ABSTRACT Declaration : public Passthrough<Declaration> {
        //  PROPERTIES  //

        /// @brief The preamble target.
        $::String::View m_name;

        /// @brief Bound declaration modifiers.
        Variable::Modifiers m_modifiers = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a target.
         * @param tag                   Tag to passthrough.
         * @param name                  Target identifier.
         * @param location              Resource location.
         */
        explicit Declaration($::RTTI::Tag tag, const $::String::View& name, const Bounds& location = {}) :
            Passthrough<Declaration>(tag, location), m_name(name) {}

        /**
         * @brief Constructs a target.
         * @param tag                   Tag to passthrough.
         * @param target                Target identifier.
         */
        explicit Declaration($::RTTI::Tag tag, const Lexer::Token* target) :
            Declaration(tag, target, target->location()) {}

        /**
         * @brief Constructs a target.
         * @param tag                   Tag to passthrough.
         * @param target                Target identifier.
         * @param location              Resource location.
         */
        explicit Declaration($::RTTI::Tag tag, const Lexer::Token* target, const Bounds& location) :
            Declaration(tag, target->lexeme(), location) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the associated declaration target.
        inline constexpr $::String::View name() const noexcept { return m_name; }

        inline constexpr Variable::Modifiers& modifiers() noexcept { return m_modifiers; }
        inline constexpr const Variable::Modifiers& modifiers() const noexcept { return m_modifiers; }
    };

    /// @brief Encapsulates Declaration Preamble.
    class $_ABSTRACT Preamble : public Passthrough<Preamble, Declaration> {
        //  PROPERTIES  //

        std::vector<Decorator*> m_decorators = {};  // Runtime decorators.
        std::vector<Attribute*> m_attributes = {};  // Compile-time attributes.

       public:
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Passthrough<Preamble, Declaration>::Passthrough;

        //  PUBLIC METHODS  //

        inline constexpr std::vector<Decorator*>& decorators() noexcept { return m_decorators; }
        inline constexpr const std::vector<Decorator*>& decorators() const noexcept { return m_decorators; }

        inline constexpr std::vector<Attribute*>& attributes() noexcept { return m_attributes; }
        inline constexpr const std::vector<Attribute*>& attributes() const noexcept { return m_attributes; }
    };

}  // namespace Forge::Syntax

#endif
