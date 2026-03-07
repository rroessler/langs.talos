#ifndef _TALOS_TYPE_PARAMETER_HPP
#define _TALOS_TYPE_PARAMETER_HPP

/// Talos Modules
#include "talos/type/entity.hpp"

/// Type Modules
#include "talos/type/utility/intrinsics.hpp"

namespace Talos::Type {

    /// @brief Parameter Typing.
    class Parameter : public Abstract<Parameter> {
        //  PROPERTIES  //

        /// @brief Parameter name.
        $::String::View m_name;

        Erased m_extends;   // Extension type.
        Erased m_fallback;  // Fallback type.

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a type-parameter.
         * @param name                  Name of parameter.
         * @param extends               Extension type.
         * @param fallback              Fallback type.
         */
        explicit Parameter(const $::String::View& name, const Erased& extends = $::New().shared<Any>(),
            const Erased& fallback = $::New().shared<Unset>()) :
            m_name(name), m_extends(extends), m_fallback(fallback) {}

        //  PROPERTIES  //

        inline constexpr $::String::View name() const noexcept { return m_name; }

        inline constexpr const Erased& extends() const noexcept { return m_extends; }
        inline constexpr const Erased& fallback() const noexcept { return m_fallback; }

        inline constexpr bool required() const noexcept { return m_fallback->is<Unset>(); }
        inline constexpr Lattice lattice() const noexcept final { return m_extends->lattice(); }
        inline constexpr $::Ternary truthiness() const noexcept final { return m_extends->truthiness(); }

        /// @brief Handles coalescing parameter types.
        inline constexpr const Erased& coalesce() const noexcept { return required() ? m_extends : m_fallback; }
        inline constexpr const Erased& coalesce(const Erased& target) const noexcept {
            return target->is<Unset>() ? coalesce() : target;
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles instantiating parameters.
         * @param constraints               Generic constraints.
         */
        Erased m_infer(const Constraints& constraints) const final;

        /**
         * @brief Handles running a unification pass.
         * @param candidate             Candidate to unify.
         * @param constraints           Generic constraints.
         */
        bool m_unify(const Erased& candidate, const Constraints& constraints) const final;

        /// @brief Ensures we can "never" copy-clone parameters.
        inline Erased m_clone() const noexcept final { return const_cast<Parameter*>(this)->as<Tagged>(); }

        /**
         * @brief Handles printing the type.
         * @param os                        Output stream.
         */
        inline void m_print($::Stream::Output& os) const final {
            os << m_name;  // show the base name before items
            if (!m_extends->is<Any>()) os << ": " << *m_extends;
            if (!m_fallback->is<Unset>()) os << " = " << *m_fallback;
        }
    };

}  // namespace Talos::Type

#endif
