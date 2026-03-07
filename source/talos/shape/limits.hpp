#ifndef _TALOS_SHAPE_LIMITS_HPP
#define _TALOS_SHAPE_LIMITS_HPP

/// Talos Modules
#include "talos/forward/shape.hpp"
#include "talos/value/macros.hpp"

namespace Talos::Shape::Limits {

    //  PROPERTIES  //

    static constexpr uint32_t MAXIMUM = UINT32_MAX;
    static constexpr uint32_t THRESHOLD =
        TALOS_XX_VALUES_IMMEDIATE($_XX_ENUM_COUNT) + TALOS_XX_VALUES_OBJECT($_XX_ENUM_COUNT) 1;

}  // namespace Talos::Shape::Limits

#endif
