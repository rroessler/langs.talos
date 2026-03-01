#ifndef _XTDLIB_CONTAINER_RANGES_HPP
#define _XTDLIB_CONTAINER_RANGES_HPP

/// C++ Modules
#include <concepts>
#include <ranges>
#include <vector>

namespace $::Ranges {

    /// @brief Casts a range to a vector.
    template <std::ranges::viewable_range R>
    inline constexpr std::vector<std::ranges::range_value_t<R>> To(R&& range) {
        return std::vector(range.begin(), range.end());
    }

    /// @brief Casts a range to a typed vector.
    template <class T, std::ranges::viewable_range R>
    inline constexpr std::vector<T> To(R&& range) {
        static_assert(std::convertible_to<std::ranges::range_value_t<R>, T>);
        return std::vector<T>(range.begin(), range.end());  // can cast safely
    }

    /// @brief Replaces a vector with the given values.
    template <class T, std::ranges::viewable_range R>
    inline constexpr std::vector<T>& Assign(std::vector<T>& target, R&& input) {
        return target.assign(input.begin(), input.end()), target;
    }

    /// @brief Appends an input range to a vector.
    template <class T, std::ranges::viewable_range U>
    inline constexpr std::vector<T>& Append(std::vector<T>& target, U&& input) {
        target.reserve(target.size() + input.size());  // reserve total size
        return target.insert(target.end(), input.begin(), input.end()), target;
    }

    /// @brief Prepends an input range to a vector.
    template <class T, std::ranges::viewable_range U>
    inline constexpr std::vector<T>& Prepend(std::vector<T>& target, U&& input) {
        target.reserve(target.size() + input.size());  // reserve total size
        return target.insert(target.begin(), input.begin(), input.end()), target;
    }

}  // namespace $::Ranges

#endif
