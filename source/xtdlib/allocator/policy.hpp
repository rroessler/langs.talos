#ifndef _XTDLIB_ALLOCATOR_POLICY_HPP
#define _XTDLIB_ALLOCATOR_POLICY_HPP

/// Library Includes
#include "xtdlib/allocator/category.hpp"
#include "xtdlib/debug/location.hpp"

namespace $::Allocator::Policy {

    /// @brief Handles validating policies.
    template <class T>
    concept Validate = requires {
        requires requires(size_t count, const Location& location, const Category& category) {
            { T::allocate(count) } -> std::same_as<void*>;
            { T::allocate(count, location) } -> std::same_as<void*>;
            { T::allocate(count, location, category) } -> std::same_as<void*>;
        };

        requires requires(void* pointer) {
            { T::deallocate(pointer) } -> std::same_as<void>;
        };

        requires requires() {
            { T::max_size() } -> std::same_as<size_t>;
        };
    };

    /// @brief Standard Allocation Policy.
    struct Standard;

    /// @brief Deterministic Allocation Policy.
    struct Deterministic;

    /// @brief Declaring a Defaulted Policy.
    using Default = Standard;

    /// @brief Aligned Allocation Policy.
    template <size_t A = 0, Policy::Validate P = Policy::Default>
    struct Uniform;

}  // namespace $::Allocator::Policy

#endif
