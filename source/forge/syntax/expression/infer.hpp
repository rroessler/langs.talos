#ifndef _FORGE_EXPRESSION_INFER_HPP
#define _FORGE_EXPRESSION_INFER_HPP

/// Forge Modules
#include "forge/syntax/node.hpp"

namespace Forge::Syntax {

    /// @brief Infer Expression Node.
    class Infer : public Abstract<Infer, Expression> {
        //  PROPERTIES  //

        /// @brief Encapsulates negation of results.
        bool m_negate = false;

        /// @brief Expression value.
        Expression* m_value;

        /// @brief Expression guard.
        Annotation* m_guard;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an inferrence expression.
         * @param value                     Inferrence value.
         * @param guard                     Guard value.
         * @param negate                    Negation flag.
         */
        explicit Infer(Expression* value, Annotation* guard, bool negate = false) :
            Infer(value, guard, negate, value->traits()->location()) {}

        /**
         * @brief Constructs an inferrence expression.
         * @param value                     Inferrence value.
         * @param guard                     Guard value.
         * @param location                  Resource location.
         */
        explicit Infer(Expression* value, Annotation* guard, const Bounds& location) :
            Abstract(location), m_value(value), m_guard(guard) {}

        /**
         * @brief Constructs an inferrence expression.
         * @param value                     Inferrence value.
         * @param guard                     Guard value.
         * @param negate                    Negation flag.
         * @param location                  Resource location.
         */
        explicit Infer(Expression* value, Annotation* guard, bool negate, const Bounds& location) :
            Abstract(location), m_negate(negate), m_value(value), m_guard(guard) {}

        //  PUBLIC METHODS  //

        inline constexpr bool negate() const noexcept { return m_negate; }
        inline constexpr Expression* value() const noexcept { return m_value; }
        inline constexpr Annotation* guard() const noexcept { return m_guard; }
    };

}  // namespace Forge::Syntax

#endif
