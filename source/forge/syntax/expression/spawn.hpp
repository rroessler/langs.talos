#ifndef _FORGE_EXPRESSION_SPAWN_HPP
#define _FORGE_EXPRESSION_SPAWN_HPP

/// Syntax Modules
#include "forge/syntax/expression/call.hpp"

namespace Forge::Syntax {

    /// @brief Spawn Expression Node.
    class Spawn : public Abstract<Spawn, Expression> {
        //  PROPERTIES  //

        /// @brief The call expression.
        Call* m_invocation;

        /// @brief Prepare the suitably function policy.
        Function::Policy m_policy = Function::Policy::ASYNC;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a policy-based invocation.
         * @param invocation                Call node.
         * @param location                  Bound location.
         */
        explicit Spawn(Call* invocation) : Spawn(invocation, invocation->traits()->location()) {}
        explicit Spawn(Call* invocation, const Bounds& location) : Abstract(location), m_invocation(invocation) {}

        /**
         * @brief Constructs a policy-based invocation.
         * @param invocation                Call node.
         * @param policy                    Function policy.
         */
        explicit Spawn(Call* invocation, Function::Policy policy) :
            Spawn(invocation, policy, invocation->traits()->location()) {}

        /**
         * @brief Constructs a policy-based invocation.
         * @param invocation                Call node.
         * @param policy                    Function policy.
         * @param location                  Bound location.
         */
        explicit Spawn(Call* invocation, Function::Policy policy, const Bounds& location) :
            Abstract(location), m_invocation(invocation), m_policy(policy) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the expected function policy.
        inline constexpr Function::Policy policy() const noexcept { return m_policy; }

        /// @brief The underlying call node.
        inline constexpr Call* invocation() const noexcept { return m_invocation; }

        /// @brief Gets the calling expression.
        inline constexpr Expression* callee() const noexcept { return m_invocation->callee(); }

        /// @brief Gets the bound arguments.
        inline constexpr const std::vector<Expression*>& arguments() const noexcept {
            return m_invocation->arguments();
        }
    };

}  // namespace Forge::Syntax

#endif
