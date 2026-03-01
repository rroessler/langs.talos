#ifndef _FORGE_NUMBER_MATH_HPP
#define _FORGE_NUMBER_MATH_HPP

/// Forge Modules
#include "forge/number/limits.hpp"

namespace Forge::Number::Math {

    /**
     * @brief Handles comparing integer values.
     * @param left                  Left value.
     * @param right                 Right value.
     */
    static inline constexpr int64_t compare(Underlying left, Underlying right) {
        auto difference = left - right;  // get the base difference to use
        return std::fabs(difference) < Limits::EPSILON ? 0 : difference < 0 ? -1 : 1;
    }

    /**
     * @brief Checks if a value is a valid integral.
     * @param value                 Value to check.
     */
    static inline constexpr bool integral(Underlying value) {
        static constexpr auto mantissa = 52;
        auto bits = std::bit_cast<uint64_t>(value);
        int32_t exponent = ((bits >> mantissa) & 0x7FF) - 1023;
        int32_t fraction = mantissa - exponent;  // get the fraction
        uint64_t mask = exponent < 0 ? 0x7FFFFFFFFFFFFFFFLL : 0x00;
        if (exponent > mantissa) mask = (1LL << fraction) - 1;
        return !(bits & mask);  // and finally check against the mask
    }

    /**
     * @brief Gets the sign of a value.
     * @param value                 Value to resolve.
     */
    static inline constexpr Underlying signum(Underlying value) {
        return (Underlying(0) < value) - (value < Underlying(0));
    }

}  // namespace Forge::Number::Math

#endif
