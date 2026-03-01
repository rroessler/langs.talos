#ifndef _FORGE_LEXER_BUFFER_HPP
#define _FORGE_LEXER_BUFFER_HPP

/// Forge Includes
#include "forge/lexer/token.hpp"

namespace Forge::Lexer {

    /// @brief Token Buffer Container.
    class Buffer {
        //  PROPERTIES  //

        /// @brief Denotes if comments are kept.
        bool m_comments = false;

        /// @brief Attached token values.
        std::vector<Token> m_tokens = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a token buffer.
         * @param comments              Comments flag.
         */
        explicit Buffer(bool comments = false) : m_comments(comments) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the total tokens bound.
        inline constexpr size_t size() const noexcept { return m_tokens.size(); }

        /// @brief Denotes if comments are contained within the buffer.
        inline constexpr bool comments() const noexcept { return m_comments; }

        /// @brief Gets the underlying token buffer.
        inline std::vector<Token>& buffer() { return m_tokens; }
        inline const std::vector<Token>& buffer() const { return m_tokens; }

        /**
         * @brief Handles appending a token.
         * @param token                 Token to append.
         */
        inline void append(Token&& token) {
            $_ASSERT(token.kind() != Kind::MISC_MAX, "Invalid token");
            if (token.kind() == Kind::MISC_CMT && !m_comments) return;
            m_tokens.emplace_back(std::move(token));  // valid token
        }
    };

}  // namespace Forge::Lexer

#endif
