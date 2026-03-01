#ifndef _FORGE_NUMBER_LIMITS_HPP
#define _FORGE_NUMBER_LIMITS_HPP

/// C++ Modules
#include <cfloat>

/// Forge Modules
#include "forge/number/underlying.hpp"

namespace Forge::Number::Limits {

    //  PROPERTIES  //

    /// @brief Maximum digits available for a number.
    static constexpr size_t DIGITS = 8 * sizeof(Underlying) - 1;

    static constexpr Underlying MINIMUM = DBL_MIN;  // Minimum value allowed.
    static constexpr Underlying MAXIMUM = DBL_MAX;  // Maximum value allowed.

    /// @brief Maximum allowed fraction digits.
    static constexpr size_t FRACTION = 100;

    /// @brief The helper "epsilon" value.
    static constexpr Underlying EPSILON = std::numeric_limits<Underlying>().epsilon();

}  // namespace Forge::Number::Limits

#endif
