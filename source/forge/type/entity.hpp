#ifndef _FORGE_TYPE_ENTITY_HPP
#define _FORGE_TYPE_ENTITY_HPP

/// Forge Modules
#include "forge/resource/location.hpp"
#include "forge/variable/captures.hpp"
#include "forge/variable/modifiers.hpp"

/// Type Modules
#include "forge/type/utility/intrinsics.hpp"

namespace Forge::Type {

    /// @brief Encapsulates a type/value pairing.
    class Entity {
        //  PROPERTIES  //

        /// @brief Bound captures context.
        Variable::Entry m_context = 0;

        /// @brief Bound entity modifiers.
        Variable::Modifiers m_modifiers = {};

        Erased m_type = $::New().shared<Unset>();   // World-of-types reference.
        Erased m_value = $::New().shared<Unset>();  // World-of-values reference.

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted type-entity.
        constexpr Entity() = default;

        /**
         * @brief Constructs an entity.
         * @param value                 Value reference.
         */
        constexpr Entity(const Erased& value) : m_value(value) {}

        /**
         * @brief Constructs an entity with initial flags.
         * @param value                 Value to bind.
         * @param flags                 Variable flags.
         */
        template <std::convertible_to<Variable::Flag>... Fs>
        constexpr Entity(const Erased& value, Fs&&... flags) :
            m_modifiers(std::forward<Fs>(flags)...), m_value(value) {}

        /**
         * @brief Constructs an entity.
         * @param value                 Value reference.
         * @param type                  Type reference.
         */
        constexpr Entity(const Erased& value, const Erased& type) : m_type(type), m_value(value) {}

        //  PUBLIC METHODS  //

        inline constexpr bool opaque() const noexcept { return !m_value->is<Unset>(); }
        inline constexpr bool transient() const noexcept { return !m_type->is<Unset>(); }
        inline constexpr bool unset() const noexcept { return m_value->is<Unset>() && m_type->is<Unset>(); }

        /// @brief Handles setting the unused state.
        inline constexpr bool unused(bool state) noexcept {
            return m_modifiers.flip(Variable::Flag::OWNED, !state), !state;
        }

        /// @brief Gets the current unused details.
        inline constexpr bool unused() const noexcept {
            return !m_modifiers.test(Variable::Flag::OWNED) && !exported();
        }

        inline constexpr Variable::Entry& context() noexcept { return m_context; }
        inline constexpr Variable::Entry context() const noexcept { return m_context; }

        inline constexpr Erased& type() noexcept { return m_type; }
        inline constexpr Erased type() const noexcept { return m_type; }

        inline constexpr Erased& value() noexcept { return m_value; }
        inline constexpr Erased value() const noexcept { return m_value; }

        inline constexpr Variable::Modifiers& modifiers() noexcept { return m_modifiers; }
        inline constexpr const Variable::Modifiers& modifiers() const noexcept { return m_modifiers; }

        inline constexpr bool exported() const noexcept { return m_modifiers.test(Variable::Flag::EXPORT); }
        inline constexpr bool immutable() const noexcept { return !m_modifiers.test(Variable::Flag::MUTABLE); }
        inline constexpr bool optional() const noexcept { return m_modifiers.test(Variable::Flag::OPTIONAL); }

        /// @brief Handles inferring an entity with constraints.
        inline constexpr Entity infer(const Constraints& constraints) const noexcept {
            // prepare the clone to be used now
            auto inferred = Entity(*this);

            // otherwise we should update our base types now
            inferred.m_type = m_type->infer(constraints);
            inferred.m_value = m_value->infer(constraints);

            // and return the resulting clone of the entity now
            return inferred;
        }
    };

}  // namespace Forge::Type

#endif
