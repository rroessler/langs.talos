#ifndef _FORGE_DECLARATION_VARIABLE_HPP
#define _FORGE_DECLARATION_VARIABLE_HPP

/// Syntax Modules
#include "forge/syntax/declaration/preamble.hpp"

namespace Forge::Syntax {

    /// @brief Variable Declaration Node.
    struct Variable : public Abstract<Variable, Preamble> {
        //  TYPEDEFS  //

        /// @brief Allow use of variable flags here.
        using Flag = ::Forge::Variable::Flag;

        /// @brief Available variable modifiers.
        using Modifiers = ::Forge::Variable::Modifiers;

       private:
        //  PROPERTIES  //

        /// @brief Type annotation hint.
        Annotation* m_hint = nullptr;

        /// @brief Associated initial value.
        Expression* m_initializer = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a variable declaration.
         * @param name                      Target name.
         * @param location                  Resource location.
         */
        explicit Variable(const $::String::View& name, const Bounds& location = {}) :
            Variable(name, nullptr, nullptr, location) {}

        /**
         * @brief Constructs a variable declaration.
         * @param target                    Target name.
         */
        explicit Variable(const Lexer::Token* target) : Variable(target, nullptr, nullptr) {}

        /**
         * @brief Constructs a variable declaration.
         * @param name                      Target name.
         * @param hint                      Type annotation.
         * @param location                  Resource location.
         */
        explicit Variable(const $::String::View& name, Expression* initializer, const Bounds& location = {}) :
            Variable(name, nullptr, initializer, location) {}

        /**
         * @brief Constructs a variable declaration.
         * @param target                    Target name.
         * @param initializer               Initializer value.
         */
        explicit Variable(const Lexer::Token* target, Expression* initializer) :
            Variable(target, nullptr, initializer) {}

        /**
         * @brief Constructs a variable declaration.
         * @param name                      Target name.
         * @param initializer               Initializer value.
         * @param location                  Resource location.
         */
        explicit Variable(const $::String::View& name, Annotation* hint, const Bounds& location = {}) :
            Variable(name, hint, nullptr, location) {}

        /**
         * @brief Constructs a variable declaration.
         * @param target                    Target name.
         * @param hint                      Type annotation.
         */
        explicit Variable(const Lexer::Token* target, Annotation* hint) : Variable(target, hint, nullptr) {}

        /**
         * @brief Constructs a variable declaration.
         * @param target                    Target name.
         * @param hint                      Type annotation.
         * @param initializer               Initializer value.
         */
        explicit Variable(const Lexer::Token* target, Annotation* hint, Expression* initializer) :
            Abstract(target), m_hint(hint), m_initializer(initializer) {}

        /**
         * @brief Constructs a variable declaration.
         * @param name                      Target name.
         * @param hint                      Type annotation.
         * @param initializer               Initializer value.
         * @param location                  Resource location.
         */
        explicit Variable(
            const $::String::View& name, Annotation* hint, Expression* initializer, const Bounds& location = {}) :
            Abstract(name, location), m_hint(hint), m_initializer(initializer) {}

        //  PUBLIC METHODS  //

        inline constexpr Annotation* hint() const noexcept { return m_hint; }
        inline constexpr Expression* initializer() const noexcept { return m_initializer; }

        inline constexpr bool required() const noexcept { return !optional() && !m_initializer; }
        inline constexpr bool optional() const noexcept { return modifiers().test(Flag::OPTIONAL); }
        inline constexpr bool immutable() const noexcept { return !modifiers().test(Flag::MUTABLE); }
        inline constexpr bool disposable() const noexcept { return modifiers().test(Flag::DISPOSABLE); }
    };

}  // namespace Forge::Syntax

#endif
