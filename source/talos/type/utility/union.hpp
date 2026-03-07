#ifndef _TALOS_TYPE_UNION_HPP
#define _TALOS_TYPE_UNION_HPP

/// Type Modules
#include "talos/type/utility/intrinsics.hpp"

namespace Talos::Type {

    /// @brief Union Typing.
    class Union : public Abstract<Union> {
        //  PROPERTIES  //

        /// @brief Potential union types.
        std::vector<Erased> m_elements;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a union type.
         * @param elements                  Elements to hold.
         */
        explicit Union(const std::vector<Erased>& elements = {}) : m_elements(elements) {}

        //  PUBLIC METHODS  //

        /// @brief Gets a nodes associated truthiness.
        inline constexpr $::Ternary truthiness() const noexcept final {
            auto predicate = [](const auto& state, const auto& element) { return state && element->truthiness(); };
            return std::ranges::fold_left(m_elements, $::Ternary(false), predicate);  // attempt resolving now
        }

        /// @brief Gets the underlying type-lattice.
        inline constexpr Lattice lattice() const noexcept final {
            auto predicate = [](const Lattice& acc, const auto& element) { return acc | element->lattice(); };
            return std::ranges::fold_left(m_elements, Lattice(), predicate);  // attempt resolving the type-lattice
        }

        /// @brief Denotes if the union is empty.
        inline constexpr bool never() const noexcept { return m_elements.empty(); }

        /// @brief Gets the union elements.
        inline constexpr const std::vector<Erased>& elements() const noexcept { return m_elements; }

        /// @brief Gets the associated "maybe" typing.
        inline constexpr Erased maybe() const noexcept {
            // ignore if we do not have the correct number of elements.
            if (m_elements.size() != 2) return nullptr;

            // pull out both elements to be queried
            auto first = m_elements.at(0), second = m_elements.at(1);

            // determine whether either is none or not
            auto fn = first->is<None>(), sn = second->is<None>();

            // and resolve to a suitable maybe element now
            return fn == sn ? nullptr : fn ? second : first;
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles type-instantiation.
         * @param constraints               Generic constraints.
         */
        Erased m_infer(const Constraints& constraints) const final;

        /**
         * @brief Checks if candidate is a subtype of this type.
         * @param candidate             Candidate to compare.
         * @param constraints           Generic constraints.
         */
        bool m_unify(const Erased& candidate, const Constraints& constraints) const final;

        /**
         * @brief Handles printing the type.
         * @param os                        Output stream.
         */
        inline void m_print($::Stream::Output& os) const final {
            if (m_elements.empty()) os << "Never";  // empty union type
            else if (auto type = maybe()) os << *type << '?';
            else os << "Union[" << $::Convert::join(m_elements) << ']';
        }
    };

    /// @brief Hidden Never Typing.
    struct Never : public Union {
        //  CONSTRUCTORS  //

        /// @brief Constructs an empty union typing.
        explicit Never() = default;
    };

    /// @brief Hidden Maybe Typing.
    struct Maybe : public Union {
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a maybe typing.
         * @param some                      Some value.
         */
        explicit Maybe(const Erased& some) : Union({ $::New().shared<None>(), some }) {}
    };

}  // namespace Talos::Type

#endif
