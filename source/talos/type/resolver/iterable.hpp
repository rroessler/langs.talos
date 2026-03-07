#ifndef _TALOS_TYPE_ITERABLE_HPP
#define _TALOS_TYPE_ITERABLE_HPP

/// Type Modules
#include "talos/type/utility/transform.hpp"

namespace Talos::Type::Utility {

    /// @brief Iterable Type Resolver.
    struct Iterable {
        //  CONSTRUCTORS  //

        /// @brief Default constructor.
        explicit Iterable() = default;

        //  OPERATOR METHODS  //

        /**
         * @brief Handles awaiting a target.
         * @param target                Target to await.
         * @param constraints           Constraints to use.
         */
        Erased operator()(const Erased& target, const Constraints& constraints) const noexcept;

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles awaiting a target.
         * @param target                Target to await.
         * @param constraints           Constraints to use.
         */
        Erased m_resolve(const Erased& target, const Constraints& constraints) const noexcept;
    };

    /// @brief Ensure the resolution conversion is valid.
    static_assert(std::convertible_to<Iterable, Resolver>);

}  // namespace Talos::Type::Utility

#endif
