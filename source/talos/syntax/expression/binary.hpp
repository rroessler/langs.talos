#ifndef _TALOS_EXPRESSION_BINARY_HPP
#define _TALOS_EXPRESSION_BINARY_HPP

/// Talos Modules
#include "talos/operator/traits.hpp"
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

    /// @brief Binary Expression Node.
    class Binary : public Abstract<Binary, Expression> {
        //  PROPERTIES  //

        /// @brief Binary operator.
        Operator::Kind m_opcode;

        Expression* m_left;   // LHS expression.
        Expression* m_right;  // RHS expression.

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a binary expression.
         * @param token                     Binary token.
         * @param left                      LHS expression.
         * @param right                     RHS expression.
         */
        explicit Binary(const Lexer::Token* token, Expression* left, Expression* right) :
            Binary(token, left, right, token->location()) {}

        /**
         * @brief Constructs a binary expression.
         * @param token                     Binary token.
         * @param left                      LHS expression.
         * @param right                     RHS expression.
         */
        explicit Binary(const Lexer::Token* token, Expression* left, Expression* right, const Bounds& location) :
            Binary(token->kind(), left, right, location) {}

        /**
         * @brief Constructs a binary expression.
         * @param opcode                    Binary opcode.
         * @param left                      LHS expression.
         * @param right                     RHS expression.
         * @param location                  Resource location.
         */
        explicit Binary(Lexer::Kind opcode, Expression* left, Expression* right, const Bounds& location = {}) :
            Binary(static_cast<Operator::Kind>(opcode), left, right, location) {}

        /**
         * @brief Constructs a binary expression.
         * @param opcode                    Binary opcode.
         * @param left                      LHS expression.
         * @param right                     RHS expression.
         * @param location                  Resource location.
         */
        explicit Binary(Operator::Kind opcode, Expression* left, Expression* right, const Bounds& location = {}) :
            Abstract(location), m_opcode(opcode), m_left(left), m_right(right) {
            $_ASSERT(::Talos::Operator::Binary(m_opcode), "Expected a binary opcode");
        }

        //  PUBLIC METHODS  //

        inline constexpr Expression* left() const noexcept { return m_left; }
        inline constexpr Expression* right() const noexcept { return m_right; }
        inline constexpr Operator::Kind opcode() const noexcept { return m_opcode; }
        inline constexpr $::String::View symbol() const noexcept { return ::Talos::Operator::Traits::name(m_opcode); }

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles folding binary values.
        Value::Any m_fold() const noexcept final;

        /**
         * @brief Handles folding two given values.
         * @param left              Left value to fold.
         * @param right             Right value to fold.
         */
        Value::Any m_fold(Value::Any left, Value::Any right) const noexcept;
    };

}  // namespace Talos::Syntax

#endif
