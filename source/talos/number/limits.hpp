#ifndef _TALOS_NUMBER_LIMITS_HPP
#define _TALOS_NUMBER_LIMITS_HPP

/// Talos Includes
#include "talos/forward/number.hpp"

namespace Talos::Number::Limits {

//  PROPERTIES  //

/// @brief Maximum digits available for a number.
static constexpr size_t DIGITS = 8 * sizeof(Floating) - 1;

static constexpr Floating MINIMUM = DBL_MIN; // Minimum value allowed.
static constexpr Floating MAXIMUM = DBL_MAX; // Maximum value allowed.

/// @brief Maximum allowed fraction digits.
static constexpr size_t FRACTION = 100;

/// @brief The helper "epsilon" value.
static constexpr Floating EPSILON = std::numeric_limits<Floating>().epsilon();

} // namespace Talos::Number::Limits

#endif
