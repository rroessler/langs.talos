#ifndef _FORGE_LITERAL_VOID_HPP
#define _FORGE_LITERAL_VOID_HPP

/// Forge Modules
#include "forge/syntax/node.hpp"

namespace Forge::Syntax {

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

}  // namespace Forge::Syntax

#endif
