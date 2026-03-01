#ifndef _FORGE_SHAPE_LIMITS_HPP
#define _FORGE_SHAPE_LIMITS_HPP

/// Forge Modules
#include "forge/forward/shape.hpp"
#include "forge/value/macros.hpp"

namespace Forge::Shape::Limits {

    //  PROPERTIES  //

    static constexpr uint32_t MAXIMUM = UINT32_MAX;
    static constexpr uint32_t THRESHOLD =
        FORGE_XX_VALUES_IMMEDIATE($_XX_ENUM_COUNT) + FORGE_XX_VALUES_OBJECT($_XX_ENUM_COUNT) 1;

}  // namespace Forge::Shape::Limits

#endif
