#ifndef _TALOS_TYPE_INSTANCE_HPP
#define _TALOS_TYPE_INSTANCE_HPP

/// Talos Modules
#include "talos/object/instance.hpp"

/// Type Modules
#include "talos/type/compound/prototype.hpp"

namespace Talos::Type {

    /// @brief Instance Typing.
    class Instance : public Abstract<Instance> {
        //  PROPERTIES  //

        /// @brief Associated class typing.
        $::Ptr::Shared<Prototype> m_prototype = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a dynamic object instance.
        explicit Instance() = default;

        /**
         * @brief Constructs an instance-type.
         * @param prototype             Class prototype.
         */
        explicit Instance(const $::Ptr::Shared<Prototype>& prototype) : m_prototype(prototype) {}

        //  PROPERTIES  //

        /// @brief Gets the underlying prototype.
        inline constexpr const $::Ptr::Shared<Prototype>& prototype() const noexcept { return m_prototype; }

        /// @brief Gets the associated type-lattice.
        Lattice lattice() const noexcept final;

        /// @brief Gets the associated truthiness.
        $::Ternary truthiness() const noexcept final;

        /**
         * @brief Handles looking up fields.
         * @param field                 Field to lookup.
         */
        Entity lookup(const $::String::View& field) const final;

        /**
         * @brief Handles transforming the type.
         * @param kind                  Operator kind.
         */
        Erased apply(Operator::Kind kind) const final;
        Erased apply(Operator::Kind kind, const Erased& right) const final;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles validating "Object" shapes.
         * @param shape                     Shape to validate.
         */
        inline constexpr bool m_extends(Shape::Underlying shape) const noexcept final {
            return m_prototype ? m_prototype->m_derived(shape) : shape == Shape::Lookup<Object::Instance>();
        }

        /**
         * @brief Handles inferring class types.
         * @param constraints               Generic constraints.
         */
        Erased m_infer(const Constraints& constraints) const final;

        /**
         * @brief Handles running a unification pass.
         * @param candidate                 Candidate to unify.
         * @param constraints               Generic parameter constraints.
         */
        bool m_unify(const Erased& candidate, const Constraints& constraints) const final;

        /**
         * @brief Handles printing the type.
         * @param os                        Output stream.
         */
        void m_print($::Stream::Output& os) const final;
    };

}  // namespace Talos::Type

#endif
