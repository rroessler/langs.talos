#ifndef _FORGE_TYPE_TRANSFORM_HPP
#define _FORGE_TYPE_TRANSFORM_HPP

/// Forge Modules
#include "forge/type/entity.hpp"

namespace Forge::Type {

    /// @brief Transformation Resolver Functor.
    using Resolver = $::Functor::Shared<Erased(const Erased&, const Constraints&)>;

    /// @brief Lazy Type Evaluation.
    class Transform : public Abstract<Transform> {
        //  PROPERTIES  //

        /// @brief The baseline target.
        Erased m_target = $::New().shared<Any>();

        /// @brief Bound resolvers available.
        Resolver m_resolver = [](const Erased& target, const Constraints&) { return target; };

       public:
        //  PUBLIC METHODS  //

        /// @brief Constructs a no-op transformation.
        explicit Transform() = default;

        /**
         * @brief Constructs a transformation.
         * @param target                Target to transform.
         * @param resolver              Resolver to inherit.
         */
        explicit Transform(const Erased& target, Resolver resolver) : m_target(target), m_resolver(resolver) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the associated type-lattice of the target.
        inline constexpr Lattice lattice() const noexcept final { return reduce()->lattice(); }

        /// @brief Gets the associated truthiness of the target.
        inline constexpr $::Ternary truthiness() const noexcept final { return reduce()->truthiness(); }

        /// @brief Allow getting the attached target.
        inline constexpr Erased& target() noexcept { return m_target; }
        inline constexpr const Erased& target() const noexcept { return m_target; }

        /**
         * @brief Handles reducing a target against constraints.
         * @param constraints           Constraints to resolve.
         */
        inline constexpr Erased reduce(const Constraints& constraints = nullptr) const {
            return m_resolver(m_target, constraints);
        }

        /**
         * @brief Handles looking up fields.
         * @param field                     Field to lookup.
         */
        inline Entity lookup(const $::String::View& field) const final { return reduce()->lookup(field); }

        /**
         * @brief Handles transforming the type.
         * @param kind                      Operator kind.
         */
        inline Erased apply(Operator::Kind kind) const final { return reduce()->apply(kind); }

        /**
         * @brief Handles transforming the type.
         * @param kind                      Operator kind.
         * @param right                     RHS value to use.
         */
        inline Erased apply(Operator::Kind kind, const Erased& right) const final {
            return reduce()->apply(kind, right);
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles validating transform shapes.
         * @param shape                     Shape to validate.
         */
        inline constexpr bool m_extends(Shape::Underlying shape) const noexcept final {
            return reduce()->m_extends(shape);
        }

        /**
         * @brief Handles instantiating a transform.
         * @param constraints               Generic constraints.
         */
        inline Erased m_infer(const Constraints& constraints) const final {
            return reduce(constraints)->m_infer(constraints);
        }

        /**
         * @brief Handles running a unification pass.
         * @param candidate                 Candidate to unify.
         * @param constraints               Generic constraints.
         */
        inline bool m_unify(const Erased& candidate, const Constraints& constraints) const final {
            return reduce(constraints)->m_unify(candidate, constraints);
        }

        /// @brief Handles cloning to the inherited class implementation.
        inline Erased m_clone() const noexcept final { return $::New().shared<Transform>(*Tagged::m_as<Transform>()); }

        /**
         * @brief Handles printing the type.
         * @param os                        Output stream.
         */
        inline void m_print($::Stream::Output& os) const final { os << *reduce(); }
    };

}  // namespace Forge::Type

#endif
