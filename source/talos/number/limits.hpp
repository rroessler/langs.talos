#ifndef _TALOS_NUMBER_LIMITS_HPP
#define _TALOS_NUMBER_LIMITS_HPP

/// C++ Modules
#include <cfloat>

/// Talos Modules
#include "talos/number/underlying.hpp"

namespace Talos::Number::Limits {

    //  PROPERTIES  //

    /// @brief Maximum digits available for a number.
    static constexpr size_t DIGITS = 8 * sizeof(Underlying) - 1;

    static constexpr Underlying MINIMUM = DBL_MIN;  // Minimum value allowed.
    static constexpr Underlying MAXIMUM = DBL_MAX;  // Maximum value allowed.

    /// @brief Maximum allowed fraction digits.
    static constexpr size_t FRACTION = 100;

    /// @brief The helper "epsilon" value.
    static constexpr Underlying EPSILON = std::numeric_limits<Underlying>().epsilon();

}  // namespace Talos::Number::Limits

#endif
