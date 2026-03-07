#ifndef _TALOS_TYPE_GENERIC_HPP
#define _TALOS_TYPE_GENERIC_HPP

/// Type Modules
#include "talos/type/utility/parameter.hpp"

namespace Talos::Type {

    /// @brief Generic Typing.
    class Generic : public Abstract<Generic> {
        //  PROPERTIES  //

        /// @brief Encapsulated body.
        Erased m_target;

        /// @brief Generic parameters list.
        Template m_parameters;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a generic type.
         * @param target                    Target to wrap.
         * @param parameters                Parameter types.
         */
        explicit Generic(const Erased& target, const Template& parameters = {}) :
            m_target(target), m_parameters(parameters) {}

        //  PROPERTIES  //

        /// @brief Gets the arity of the generic typing.
        inline constexpr size_t arity() const noexcept {
            static constexpr auto s_predicate = [](const auto& parameter) { return parameter->required(); };
            return std::ranges::count_if(m_parameters, s_predicate);  // count all items that are required
        }

        /// @brief Gets the adicity of the generic typing.
        inline constexpr size_t adicity() const noexcept { return m_parameters.size(); }

        inline constexpr Lattice lattice() const noexcept final { return m_target->lattice(); }
        inline constexpr $::Ternary truthiness() const noexcept final { return m_target->truthiness(); }

        inline constexpr const Erased& target() const noexcept { return m_target; }
        inline constexpr const Template& parameters() const noexcept { return m_parameters; }

        /**
         * @brief Instantiates a generic with arguments.
         * @param arguments                 Arguments to instantiate.
         */
        Erased instantiate(std::vector<Erased> arguments) const;

        /**
         * @brief Handles looking up fields.
         * @param field                     Field to lookup.
         */
        inline Entity lookup(const $::String::View& field) const final { return m_target->lookup(field); }

        /**
         * @brief Handles transforming the type.
         * @param kind                      Operator kind.
         */
        inline Erased apply(Operator::Kind kind) const final { return m_target->apply(kind); }

        /**
         * @brief Handles transforming the type.
         * @param kind                      Operator kind.
         * @param right                     RHS value to use.
         */
        inline Erased apply(Operator::Kind kind, const Erased& right) const final {
            return m_target->apply(kind, right);
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles validating generic shapes.
         * @param shape                     Shape to validate.
         */
        inline constexpr bool m_extends(Shape::Underlying shape) const noexcept final {
            return m_target->m_extends(shape);
        }

        /**
         * @brief Handles instantiating a generic.
         * @param constraints               Generic constraints.
         */
        Erased m_infer(const Constraints& constraints) const final;

        /**
         * @brief Handles running a unification pass.
         * @param candidate                 Candidate to unify.
         * @param constraints               Generic constraints.
         */
        bool m_unify(const Erased& candidate, const Constraints& constraints) const final;

        /**
         * @brief Handles printing the type.
         * @param os                        Output stream.
         * @param self                      Type instance.
         */
        void m_print($::Stream::Output& os) const final;
    };

}  // namespace Talos::Type

#endif
