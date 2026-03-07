#ifndef _TALOS_REFLECT_CATEGORY_HPP
#define _TALOS_REFLECT_CATEGORY_HPP

/// Talos Modules
#include "talos/forward/reflect.hpp"

//  X-MACROS  //

#define TALOS_XX_REFLECTION_CATEGORIES(X) \
    X(UNKNOWN, "Unknown")                 \
    X(OPERATOR, "Operator")               \
    X(OVERLOAD, "Overload")               \
    X(DEPRECATED, "Deprecated")

//  NAMESPACES  //

namespace Talos::Reflect {

    /// @brief Available Compile-Time Categories.
    $_XX_ENUM_CLASS(Category, uint8_t, TALOS_XX_REFLECTION_CATEGORIES);

}  // namespace Talos::Reflect

#endif
