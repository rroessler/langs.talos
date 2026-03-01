#ifndef _FORGE_ATTRIBUTE_OPERATOR_HPP
#define _FORGE_ATTRIBUTE_OPERATOR_HPP

/// Forge Modules
#include "forge/operator/kind.hpp"

/// Syntax Modules
#include "forge/syntax/declaration/attribute.hpp"

namespace Forge::Syntax {

    /// @brief Compile Time Operator Node.
    struct Operator : public Abstract<Operator, Attribute> {
        //  TYPEDEFS  //

        /// @brief Underlying Kind.
        using Kind = ::Forge::Operator::Kind;

       private:
        //  PROPERTIES  //

        /// @brief The underlying operator kind.
        Kind m_kind;

        /// @brief Allow setting the target.
        Annotation* m_target;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an operator overload.
         * @param kind              Kind of operator.
         * @param location          Resource location.
         */
        explicit Operator(Kind kind, const Bounds& location = {}) : Operator(kind, nullptr, location) {}

        /**
         * @brief Constructs an operator overload.
         * @param kind              Kind of operator.
         * @param target            Target to overload.
         * @param location          Resource location.
         */
        explicit Operator(Kind kind, Annotation* target, const Bounds& location = {}) :
            Abstract(Reflect::Category::OPERATOR, location), m_kind(kind), m_target(target) {}

        //  PUBLIC METHODS  //

        inline constexpr Kind kind() const noexcept { return m_kind; }
        inline constexpr const Annotation* target() const noexcept { return m_target; }
    };

}  // namespace Forge::Syntax

#endif
