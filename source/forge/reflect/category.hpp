#ifndef _FORGE_REFLECT_CATEGORY_HPP
#define _FORGE_REFLECT_CATEGORY_HPP

/// Forge Modules
#include "forge/forward/reflect.hpp"

//  X-MACROS  //

#define FORGE_XX_REFLECTION_CATEGORIES(X) \
    X(UNKNOWN, "Unknown")                 \
    X(OPERATOR, "Operator")               \
    X(OVERLOAD, "Overload")               \
    X(DEPRECATED, "Deprecated")

//  NAMESPACES  //

namespace Forge::Reflect {

    /// @brief Available Compile-Time Categories.
    $_XX_ENUM_CLASS(Category, uint8_t, FORGE_XX_REFLECTION_CATEGORIES);

}  // namespace Forge::Reflect

#endif
