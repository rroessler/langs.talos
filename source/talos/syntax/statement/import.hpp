#ifndef _TALOS_STATEMENT_IMPORT_HPP
#define _TALOS_STATEMENT_IMPORT_HPP

/// Talos Modules
#include "talos/resource/path.hpp"

/// Syntax Modules
#include "talos/syntax/literal/identifier.hpp"

namespace Talos::Syntax {

    /// @brief Import Statement Node.
    class Import : public Abstract<Import, Statement> {
        //  PROPERTIES  //

        /// @brief Denotes if a module export instead.
        bool m_exported;

        /// @brief Denotes if using wildcard naming.
        bool m_wildcard;

        /// @brief The import path given.
        $::String::View m_path;

        /// @brief Import binding patterns.
        std::vector<Identifier*> m_patterns;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an import statement.
         * @param path                  Resource path.
         * @param pattern               Wildcard pattern.
         * @param location              Resource location.
         */
        explicit Import(const $::String::View& path, Identifier* pattern, const Bounds& location = {}) :
            Import(path, pattern, false, location) {}

        /**
         * @brief Constructs an import statement.
         * @param token                 Resource token.
         * @param pattern               Wildcard pattern.
         * @param exported              Exported flag.
         */
        explicit Import(const Lexer::Token* token, Identifier* pattern, bool exported = false) :
            Import(token->lexeme(), pattern, exported, token->location()) {}

        /**
         * @brief Constructs an import statement.
         * @param token                 Resource token.
         * @param pattern               Wildcard pattern.
         * @param exported              Exported flag.
         * @param location              Resource location.
         */
        explicit Import(const Lexer::Token* token, Identifier* pattern, bool exported, const Bounds& location) :
            Import(token->lexeme(), pattern, exported, location) {}

        /**
         * @brief Constructs an import statement.
         * @param path                  Resource path.
         * @param pattern               Wildcard pattern.
         * @param exported              Exported flag.
         * @param location              Resource location.
         */
        explicit Import(const $::String::View& path, Identifier* pattern, bool exported, const Bounds& location = {}) :
            Abstract(location), m_exported(exported), m_wildcard(true), m_path(path) {
            if (pattern != nullptr) m_patterns.emplace_back(pattern);
        }

        /**
         * @brief Constructs an import statement.
         * @param path                  Resource path.
         * @param location              Resource location.
         */
        explicit Import(const $::String::View& path, const Bounds& location = {}) :
            Import(path, nullptr, false, location) {}

        /**
         * @brief Constructs an import statement.
         * @param path                  Resource path.
         * @param location              Resource location.
         */
        explicit Import(const $::String::View& path, bool exported, const Bounds& location = {}) :
            Import(path, nullptr, exported, location) {}

        /**
         * @brief Constructs an import statement.
         * @param path                  Resource path.
         * @param location              Resource location.
         */
        explicit Import(const Lexer::Token* token) : Import(token->lexeme(), nullptr, false, token->location()) {}

        /**
         * @brief Constructs an import statement.
         * @param path                  Resource path.
         * @param location              Resource location.
         */
        explicit Import(const Lexer::Token* token, const Bounds& location) :
            Import(token->lexeme(), nullptr, false, location) {}

        /**
         * @brief Constructs an import statement.
         * @param path                  Resource path.
         * @param location              Resource location.
         */
        explicit Import(const Lexer::Token* token, bool exported, const Bounds& location = {}) :
            Import(token->lexeme(), nullptr, exported, location) {}

        /**
         * @brief Constructs an import statement.
         * @param path                  Resource path.
         * @param patterns              Import patterns.
         */
        explicit Import(const Lexer::Token* token, const std::vector<Identifier*>& patterns = {}) :
            Import(token->lexeme(), patterns, false, token->location()) {}

        /**
         * @brief Constructs an import statement.
         * @param path                  Resource path.
         * @param patterns              Import patterns.
         * @param location              Resource location.
         */
        explicit Import(const $::String::View& path, std::vector<Identifier*> patterns, const Bounds& location = {}) :
            Import(path, patterns, false, location) {}

        /**
         * @brief Constructs an import statement.
         * @param path                  Resource path.
         * @param patterns              Import patterns.
         * @param location              Resource location.
         */
        explicit Import(const Lexer::Token* token, const std::vector<Identifier*>& patterns, const Bounds& location) :
            Import(token->lexeme(), patterns, false, location) {}

        /**
         * @brief Constructs an import statement.
         * @param path                  Resource path.
         * @param patterns              Import patterns.
         * @param exported              Exported flag.
         */
        explicit Import(const Lexer::Token* token, std::vector<Identifier*> patterns, bool exported = false) :
            Import(token->lexeme(), patterns, exported, token->location()) {}

        /**
         * @brief Constructs an import statement.
         * @param path                  Resource path.
         * @param patterns              Import patterns.
         * @param exported              Exported flag.
         * @param location              Resource location.
         */
        explicit Import(
            const Lexer::Token* token, std::vector<Identifier*> patterns, bool exported, const Bounds& location) :
            Import(token->lexeme(), patterns, exported, location) {}

        /**
         * @brief Constructs an import statement.
         * @param path                  Resource path.
         * @param patterns              Import patterns.
         * @param exported              Exported flag.
         * @param location              Resource location.
         */
        explicit Import(const $::String::View& path, std::vector<Identifier*> patterns, bool exported,
            const Bounds& location = {}) :
            Abstract(location), m_exported(exported), m_wildcard(false), m_path(path), m_patterns(patterns) {}

        //  PUBLIC METHODS  //

        inline constexpr bool exported() const noexcept { return m_exported; }
        inline constexpr bool wildcard() const noexcept { return m_wildcard; }
        inline constexpr $::String::View path() const noexcept { return m_path; }
        inline constexpr const std::vector<Identifier*>& patterns() const noexcept { return m_patterns; }
    };

}  // namespace Talos::Syntax

#endif
