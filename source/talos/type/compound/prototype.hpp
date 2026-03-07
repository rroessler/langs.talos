#ifndef _TALOS_TYPE_PROTOTYPE_HPP
#define _TALOS_TYPE_PROTOTYPE_HPP

/// Type Modules
#include "talos/type/compound/callable.hpp"
#include "talos/type/compound/protocol.hpp"
#include "talos/type/utility/union.hpp"

namespace Talos::Type {

    /// @brief Constructor Applicator Callback.
    using Constructor = $::Functor::Shared<Erased(const Prototype*)>;

    /// @brief Operation Applicator Callback.
    using Apply = $::Functor::Shared<Erased(const Protocol*, Operator::Kind, const Erased&)>;

    /// @brief Type Class Node.
    class Prototype : public Abstract<Prototype> {
        //  TYPEDEFS  //

        /// @brief Allow instances internal access.
        friend class Instance;

        //  PROPERTIES  //

        /// @brief Underlying shape.
        Shape::Underlying m_shape;

        /// @brief The associated protocol value.
        $::Ptr::Shared<Protocol> m_protocol;

        /// @brief Super-class typing to inherit.
        Erased m_super = $::New().shared<None>();

        /// @brief The underlying base constructor.
        Constructor m_constructor = nullptr;

        /// @brief Class operators handler.
        Apply m_operators = nullptr;

        /// @brief Static field properties available.
        $::Record<Entity> m_statics = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a class instance.
         * @param name                      Name of class.
         * @param shape                     Underlying shape.
         * @param fields                    Initial fields.
         */
        explicit Prototype(const $::String::View& name, Shape::Underlying shape, const Algorithm& fields = {}) :
            m_shape(shape), m_protocol($::New().shared<Protocol>(name, fields)) {}

        //  PUBLIC METHODS  //

        /// @brief Handles instantiating the class instance.
        $::Ptr::Shared<Instance> instantiate();

        inline constexpr Shape::Underlying shape() const noexcept { return m_shape; }
        inline constexpr $::String::View name() const noexcept { return m_protocol->name(); }

        inline constexpr $::Ternary truthiness() const noexcept final { return true; }
        inline constexpr Lattice lattice() const noexcept final { return Fact::OBJ_ANY; }

        inline constexpr Erased& super() noexcept { return m_super; }
        inline constexpr const Erased& super() const noexcept { return m_super; }

        inline constexpr Algorithm& fields() noexcept { return m_protocol->fields(); }
        inline constexpr const Algorithm& fields() const noexcept { return m_protocol->fields(); }

        inline constexpr $::Record<Entity>& statics() noexcept { return m_statics; }
        inline constexpr const $::Record<Entity>& statics() const noexcept { return m_statics; }

        inline constexpr Apply& operators() noexcept { return m_operators; }
        inline constexpr const Apply& operators() const noexcept { return m_operators; }

        inline constexpr Constructor& constructor() noexcept { return m_constructor; }
        inline constexpr const Constructor& constructor() const noexcept { return m_constructor; }

        inline constexpr std::vector<Erased>& constraints() noexcept { return m_protocol->constraints(); }
        inline constexpr const std::vector<Erased>& constraints() const noexcept { return m_protocol->constraints(); }

        /// @brief The baseline handler for constructing prototypes.
        inline constexpr Erased callable() const noexcept {
            return m_constructor ? m_constructor(this) : $::New().shared<None>();
        }

        /**
         * @brief Handles looking up static fields.
         * @param field                     Field to look up.
         */
        inline Entity lookup(const $::String::View& field) const final {
            if (m_statics.contains(field)) return m_statics.at(field);
            if (!m_super->is<Prototype>()) return Entity();
            return m_super->as<Prototype>()->lookup(field);
        }

       protected:
        //  PRIVATE METHODS  //

        /// @brief Gets the base shape value.
        inline constexpr Shape::Underlying m_base() const noexcept {
            return m_super->is<Prototype>() ? m_super->as<Prototype>()->m_base() : m_shape;
        }

        /**
         * @brief Checks if this class contains the given shape.
         * @param shape                     Shape to check.
         */
        inline constexpr bool m_derived(Shape::Underlying shape) const noexcept {
            if (m_shape == shape) return true;
            if (!m_super->is<Prototype>()) return false;
            return m_super->as<Prototype>()->m_derived(shape);
        }

        /**
         * @brief Checks if we have a class-based typing.
         * @param shape                     Shape to check.
         */
        inline constexpr bool m_extends(Shape::Underlying shape) const noexcept final {
            return shape == Shape::Lookup<Object::Class>();
        }

        /**
         * @brief Handles looking up member fields.
         * @param field                     Field to look up.
         */
        inline Entity m_lookup(const $::String::View& field) const {
            // attempt getting the baseline entity
            auto entity = m_protocol->lookup(field);
            if (!entity.unset()) return entity;

            // otherwise check against the super handler now
            if (!m_super->is<Prototype>()) return m_super->lookup(field);
            return m_super->as<Prototype>()->m_lookup(field);
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
