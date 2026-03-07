#ifndef _TALOS_EXPRESSION_UNARY_HPP
#define _TALOS_EXPRESSION_UNARY_HPP

/// Talos Modules
#include "talos/operator/traits.hpp"
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

    /// @brief Unary Expression Node.
    class Unary : public Abstract<Unary, Expression> {
        //  PROPERTIES  //

        /// @brief Unary operator.
        Operator::Kind m_opcode;

        /// @brief Associated expression value.
        Expression* m_operand;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a unary expression.
         * @param token                     Unary token.
         * @param operand                   Unary operand.
         */
        explicit Unary(const Lexer::Token* token, Expression* operand) :
            Unary(token->kind(), operand, token->location()) {}

        /**
         * @brief Constructs a unary expression.
         * @param opcode                    Unary opcode.
         * @param operand                   Unary operand.
         * @param location                  Resource location.
         */
        explicit Unary(Lexer::Kind opcode, Expression* operand, const Bounds& location = {}) :
            Unary(static_cast<Operator::Kind>(opcode), operand, location) {}

        /**
         * @brief Constructs a unary expression.
         * @param opcode                    Unary opcode.
         * @param operand                   Unary operand.
         * @param location                  Resource location.
         */
        explicit Unary(Operator::Kind opcode, Expression* operand, const Bounds& location = {}) :
            Abstract(location), m_opcode(opcode), m_operand(operand) {
            $_ASSERT(::Talos::Operator::Unary(m_opcode), "Expected a unary opcode");
        }

        //  PUBLIC METHODS  //

        inline constexpr Expression* operand() const noexcept { return m_operand; }
        inline constexpr Operator::Kind opcode() const noexcept { return m_opcode; }
        inline constexpr $::String::View symbol() const noexcept { return ::Talos::Operator::Traits::name(m_opcode); }

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles folding unary values.
        Value::Any m_fold() const noexcept final;
    };

}  // namespace Talos::Syntax

#endif
