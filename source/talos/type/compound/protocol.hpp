#ifndef _TALOS_TYPE_PROTOCOL_HPP
#define _TALOS_TYPE_PROTOCOL_HPP

/// Type Modules
#include "talos/type/utility/algorithm.hpp"

namespace Talos::Type {

    /// @brief Protocol Interface Type.
    class Protocol : public Abstract<Protocol> {
        //  PROPERTIES  //

        /// @brief Protocol field types.
        Algorithm m_fields = {};

        /// @brief Associated protocol name.
        $::String::View m_name = {};

        /// @brief Prepare a fallback typing.
        Erased m_fallback = nullptr;

        /// @brief Underlying protocol generics.
        std::vector<Erased> m_constraints = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs an empty interface.
        explicit Protocol() = default;

        /**
         * @brief Constructs a named empty interface.
         * @param name                      Name to bind.
         */
        explicit Protocol(const $::String::View& name) : m_name(name) {}

        /**
         * @brief Constructs a record typing.
         * @param fields                    Interface fields.
         */
        explicit Protocol(const Erased& fallback) : m_fallback(fallback) {}

        /**
         * @brief Constructs a protocol typing.
         * @param fields                    Interface fields.
         */
        explicit Protocol(const Algorithm& fields) : m_fields(fields) {}

        /**
         * @brief Constructs a record typing.
         * @param name                      Name to bind.
         * @param fields                    Interface fields.
         */
        explicit Protocol(const $::String::View& name, const Erased& fallback) : m_name(name), m_fallback(fallback) {}

        /**
         * @brief Constructs a protocol typing.
         * @param name                      Name to bind.
         * @param fields                    Interface fields.
         */
        explicit Protocol(const $::String::View& name, const Algorithm& fields) : m_fields(fields), m_name(name) {}
        explicit Protocol(const $::String::View& name, const $::Record<Entity>& fields) :
            m_fields(fields), m_name(name) {}

        //  PUBLIC METHODS  //

        inline constexpr $::String::View& name() noexcept { return m_name; }
        inline constexpr $::String::View name() const noexcept { return m_name; }

        inline constexpr Algorithm& fields() noexcept { return m_fields; }
        inline constexpr const Algorithm& fields() const noexcept { return m_fields; }

        inline constexpr std::vector<Erased>& constraints() noexcept { return m_constraints; }
        inline constexpr const std::vector<Erased>& constraints() const noexcept { return m_constraints; }

        inline constexpr Erased& constraints(size_t index) noexcept { return m_constraints.at(index); }
        inline constexpr const Erased& constraints(size_t index) const noexcept { return m_constraints.at(index); }

        inline constexpr $::Ternary truthiness() const noexcept final { return true; }
        inline constexpr Lattice lattice() const noexcept final { return Fact::OBJ_ANY; }

        /**
         * @brief Handles looking up fields.
         * @param field                 Field to lookup.
         */
        inline constexpr Entity lookup(const $::String::View& field) const final {
            if (auto entity = m_fields.lookup(field, this); !entity.unset()) return entity;
            return m_fallback == nullptr ? Entity() : Entity(m_fallback);  // get fallback
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles validating "Object" shapes.
         * @param shape                     Shape to validate.
         */
        inline constexpr bool m_extends(Shape::Underlying shape) const noexcept final {
            return shape == Shape::Lookup<Object::Instance>();
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
