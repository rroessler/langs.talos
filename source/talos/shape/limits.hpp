#ifndef _TALOS_SHAPE_LIMITS_HPP
#define _TALOS_SHAPE_LIMITS_HPP

/// Talos Includes
#include "talos/forward/shape.hpp"

/// Value Includes
#include "talos/value/_inline/macros.ipp"

namespace Talos::Shape::Limits {

//  PROPERTIES  //

static constexpr Underlying MAXIMUM = UINT32_MAX;
static constexpr Underlying THRESHOLD =
    TALOS_XX_VALUES_IMMEDIATE($_XX_ENUM_COUNT) + TALOS_XX_VALUES_OBJECT($_XX_ENUM_COUNT) 1;

} // namespace Talos::Shape::Limits

#endif
