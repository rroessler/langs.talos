#ifndef _FORGE_LITERAL_TEXT_HPP
#define _FORGE_LITERAL_TEXT_HPP

/// Forge Modules
#include "forge/syntax/node.hpp"

namespace Forge::Syntax {

    /// @brief Text Literal Node.
    class Text : public Abstract<Text, Expression> {
        //  PROPERTIES  //

        /// @brief Associated text value.
        $::String::View m_buffer;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a tokenized text-node.
         * @param token                 Token to bind.
         */
        explicit Text(const Lexer::Token* token) : Abstract(token), m_buffer(token->lexeme()) {}

        /**
         * @brief Constructs an explicit text-node.
         * @param buffer                Text buffer to bind.
         * @param location              Optional location.
         */
        explicit Text(const $::String::View& buffer = "", const Bounds& location = {}) :
            Abstract(location), m_buffer(buffer) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the associated value.
        inline constexpr $::String::View buffer() const noexcept { return m_buffer; }
    };

}  // namespace Forge::Syntax

#endif
