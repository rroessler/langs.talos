#ifndef _TALOS_LITERAL_NUMERIC_HPP
#define _TALOS_LITERAL_NUMERIC_HPP

/// Talos Modules
#include "talos/number/tagged.hpp"
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

    /// @brief Number Literal Node.
    class Numeric : public Abstract<Numeric, Expression> {
        //  PROPERTIES  //

        /// @brief Associated numeric value.
        Number::Underlying m_value = 0;

        /// @brief Underlying view of token.
        const Lexer::Token* m_token = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a numeric from a token.
         * @param token                     Token to resolve.
         */
        explicit Numeric(const Lexer::Token* token) : Abstract(token), m_token(token) {
            switch (token->kind()) {
                case Lexer::Kind::LTRL_FLT: m_value = std::stod(buffer(), nullptr); break;
                case Lexer::Kind::LTRL_BIN: m_value = std::stoull(buffer(), nullptr, 2); break;
                case Lexer::Kind::LTRL_OCT: m_value = std::stoull(buffer(), nullptr, 8); break;
                case Lexer::Kind::LTRL_INT: m_value = std::stoull(buffer(), nullptr, 10); break;
                case Lexer::Kind::LTRL_HEX: m_value = std::stoull(buffer(), nullptr, 16); break;
                default: $_ABORT("Unexpected numeric token");  // invalid token received
            }
        }

        /**
         * @brief Constructs a defaulted numeric.
         * @param location                  Resource location.
         */
        explicit Numeric(const Bounds& location = {}) : Abstract(location) {}

        /**
         * @brief Constructs a numeric node.
         * @param value                     Numeric value.
         * @param location                  Resource location.
         */
        explicit Numeric(Number::Underlying value, const Bounds& location = {}) : Abstract(location), m_value(value) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the associated value.
        inline constexpr Number::Underlying value() const noexcept { return m_value; }

        /// @brief Gets a buffer of the underlying numeric
        inline constexpr $::String::Buffer buffer() const noexcept {
            return m_token ? $::String::Buffer(m_token->lexeme()) : fmt::to_string(m_value);
        }

       protected:
        //  PRIVATE METHODS  //

        /// @brief Allow folding into a numeric.
        inline constexpr Value::Any m_fold() const noexcept final { return Number::Tagged(m_value); }
    };

}  // namespace Talos::Syntax

#endif
