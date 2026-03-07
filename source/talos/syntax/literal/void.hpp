#ifndef _TALOS_LITERAL_VOID_HPP
#define _TALOS_LITERAL_VOID_HPP

/// Talos Modules
#include "talos/syntax/node.hpp"

namespace Talos::Syntax {

    /// @brief Void Literal Node.
    struct Void : public Abstract<Void, Expression> {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

       protected:
        //  PRIVATE METHODS  //

        /// @brief Allow folding the return value now.
        inline constexpr Value::Any m_fold() const noexcept final { return Value::Void(); }
    };

}  // namespace Talos::Syntax

#endif
