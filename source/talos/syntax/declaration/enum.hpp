#ifndef _TALOS_DECLARATION_ENUM_HPP
#define _TALOS_DECLARATION_ENUM_HPP

/// Syntax Modules
#include "talos/syntax/declaration/preamble.hpp"

namespace Talos::Syntax {

    /// @brief Enum Variant Node.
    class Variant : public Abstract<Variant> {
        //  PROPERTIES  //

        $::String::View m_key;  // Variant key.
        Expression* m_label;    // Optional label.
        Expression* m_value;    // Optional value.

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an enum variant.
         * @param token                 Variant token.
         * @param label                 Optional label.
         * @param value                 Optional value.
         * @param location              Resource location.
         */
        explicit Variant(const Lexer::Token* token, Expression* label, Expression* value) :
            Variant(token->lexeme(), label, value, token->location()) {}

        /**
         * @brief Constructs an enum variant.
         * @param token                 Variant token.
         * @param label                 Optional label.
         * @param value                 Optional value.
         * @param location              Resource location.
         */
        explicit Variant(const Lexer::Token* token, Expression* label, Expression* value, const Bounds& location) :
            Variant(token->lexeme(), label, value, location) {}

        /**
         * @brief Constructs an enum variant.
         * @param key                   Key to bind.
         * @param label                 Optional label.
         * @param value                 Optional value.
         * @param location              Resource location.
         */
        explicit Variant(
            const $::String::View& key, Expression* label, Expression* value, const Bounds& location = {}) :
            Abstract(location), m_key(key), m_label(label), m_value(value) {}

        //  PUBLIC METHODS  //

        inline constexpr Expression* label() const noexcept { return m_label; }
        inline constexpr Expression* value() const noexcept { return m_value; }
        inline constexpr $::String::View key() const noexcept { return m_key; }
    };

    /// @brief Enum Declaration Node.
    class Enum : public Abstract<Enum, Declaration> {
        //  PROPERTIES  //

        /// @brief All enum variants.
        std::vector<Variant*> m_variants = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an enumeration.
         * @param name              Name of enum.
         * @param location          Resource location.
         */
        explicit Enum(const $::String::View& name, const Bounds& location = {}) : Enum(name, {}, location) {}

        /**
         * @brief Constructs an enumeration.
         * @param token             Name of enum.
         * @param location          Resource location.
         */
        explicit Enum(const Lexer::Token* token, const Bounds& location) : Enum(token->lexeme(), {}, location) {}

        /**
         * @brief Constructs an enumeration.
         * @param token             Name of enum.
         * @param variants          Enumeration variants.
         */
        explicit Enum(const Lexer::Token* token, const std::vector<Variant*>& variants = {}) :
            Enum(token->lexeme(), variants, token->location()) {}

        /**
         * @brief Constructs an enumeration.
         * @param name              Name of enum.
         * @param variants          Enumeration variants.
         * @param location          Resource location.
         */
        explicit Enum(const $::String::View& name, const std::vector<Variant*>& variants, const Bounds& location = {}) :
            Abstract(name, location), m_variants(variants) {}

        /**
         * @brief Constructs an enumeration.
         * @param token             Name of enum.
         * @param variants          Enumeration variants.
         * @param location          Resource location.
         */
        explicit Enum(const Lexer::Token* token, const std::vector<Variant*>& variants, const Bounds& location) :
            Enum(token->lexeme(), variants, location) {}

        //  PUBLIC METHODS  //

        /// @brief Denotes if the enumeration is empty.
        inline constexpr bool empty() const noexcept { return m_variants.empty(); }

        /// @brief Gets the available enumeration variants.
        inline constexpr const std::vector<Variant*>& variants() const noexcept { return m_variants; }
    };

}  // namespace Talos::Syntax

#endif
