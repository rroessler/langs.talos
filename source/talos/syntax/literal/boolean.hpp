#ifndef _TALOS_LITERAL_BOOLEAN_HPP
#define _TALOS_LITERAL_BOOLEAN_HPP

/// Talos Modules
#include "talos/syntax/node.hpp"
#include "talos/value/boolean.hpp"

namespace Talos::Syntax {

    /// @brief True Literal Node.
    struct True : public Abstract<True, Expression> {
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a tokenized "True" value.
         * @param token                     Token to bind.
         */
        explicit True(const Lexer::Token* token) : Abstract(token) {
            $_ASSERT(token->kind() == Lexer::Kind::LTRL_TRUE);
        }

        /**
         * @brief Constructs a defaulted "True" value.
         * @param location                  Resource location.
         */
        explicit True(const Bounds& location = {}) : Abstract(location) {}

       protected:
        //  PRIVATE METHODS  //

        /// @brief Allow folding into a truthy value.
        inline constexpr Value::Any m_fold() const noexcept final { return Value::Boolean(true); }
    };

    /// @brief False Literal Node.
    struct False : public Abstract<False, Expression> {
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a tokenized "False" value.
         * @param token                     Token to bind.
         */
        explicit False(const Lexer::Token* token) : Abstract(token) {
            $_ASSERT(token->kind() == Lexer::Kind::LTRL_FALSE);
        }

        /**
         * @brief Constructs a defaulted "False" value.
         * @param location                  Resource location.
         */
        explicit False(const Bounds& location = {}) : Abstract(location) {}

       protected:
        //  PRIVATE METHODS  //

        /// @brief Allow folding into a falsey value.
        inline constexpr Value::Any m_fold() const noexcept final { return Value::Boolean(false); }
    };

}  // namespace Talos::Syntax

#endif
