#ifndef _FORGE_LEXER_VISITOR_HPP
#define _FORGE_LEXER_VISITOR_HPP

/// Forge Includes
#include "forge/lexer/buffer.hpp"

namespace Forge::Lexer {

    /// @brief Token Visitor.
    class Visitor {
        //  PROPERTIES  //

        /// @brief Current token index.
        size_t m_index = 0;

        /// @brief Underlying token buffer.
        const Buffer* m_tokens;

        /// @brief Baseline invalid token.
        static inline const Token m_invalid = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a token-visitor.
         * @param tokens                Buffer to encapsulate.
         */
        explicit Visitor(const Buffer* tokens) : m_tokens(tokens) {}

        //  PUBLIC METHODS  //

        /// @brief Resets the parser-stream.
        inline void reset() { m_rewind(0); }

        /// @brief Denotes if at the EOS value.
        inline constexpr bool eos() const noexcept { return m_index >= m_tokens->size(); }

        /// @brief Gets the previous token view.
        inline constexpr const Token* previous() const { return peek(-1); }

        /// @brief Gets the current token view.
        inline constexpr const Token* current() const { return peek(0); }

        /// @brief Advances the stream by one-place forwards.
        inline const Token* advance() { return eos() ? &m_invalid : (++m_index, previous()); }

        /**
         * @brief Peeks a token at an offset from the current index.
         * @param offset                    Offset to peek.
         */
        inline constexpr const Token* peek(int32_t offset = 0) const noexcept {
            if (offset == INT32_MAX) return m_incoming();  // gets next non-whitespace
            else if (m_index + offset >= m_tokens->size()) return &m_invalid;
            else return &m_tokens->buffer().at(m_index + offset);
        }

       protected:
        //  PRIVATE METHODS  //

        /// @brief Gets the current index position.
        inline constexpr size_t m_tell() const noexcept { return m_index; }

        /**
         * @brief Handles rewinding the visitor position.
         * @param index                     Index to rewind.
         */
        inline constexpr void m_rewind(size_t index) { $_ASSERT(index <= m_tokens->size()), m_index = index; }

        /// @brief Gets the next non-whitespace token.
        inline constexpr const Token* m_incoming() const noexcept {
            size_t index = m_index;  // prepare the index to be used now whilst we can
            while (index < m_tokens->size() && m_tokens->buffer().at(index).kind() == Kind::MISC_CMT) ++index;
            return index > INT32_MAX ? &m_invalid : peek(index - m_index);  // and ensure that the result is valid
        }
    };

}  // namespace Forge::Lexer

#endif
