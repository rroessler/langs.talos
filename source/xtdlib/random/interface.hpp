#ifndef _XTDLIB_RANDOM_INTERFACE_HPP
#define _XTDLIB_RANDOM_INTERFACE_HPP

/// C++ Includes
#include <concepts>
#include <limits>

namespace $::Random::Device {

    /// @brief Checks for valid interface values.
    template <class T, class R = T::Output>
    concept Interface = requires(T t) {
        { t.next() } -> std::same_as<R>;
        { t.entropy() } -> std::same_as<double>;
        { t.limits() } -> std::same_as<std::numeric_limits<R>>;
        requires std::is_arithmetic_v<R>;  // and ensure numeric
    };

}  // namespace $::Random::Device

#endif
