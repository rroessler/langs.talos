#ifndef _TALOS_REFLECT_CATEGORY_HPP
#define _TALOS_REFLECT_CATEGORY_HPP

/// Talos Includes
#include "talos/forward/reflect.hpp"

//  X-MACROS  //

#define TALOS_XX_REFLECTION_FEATURES(X) X(JITTED, "Optimize")

#define TALOS_XX_REFLECTION_CATEGORIES(X) \
  X(INTERNAL, Internal, "Internal")       \
  X(OVERLOAD, Overload, "Overload")       \
  X(OPERATOR, Override, "Operator")       \
  X(DEPRECATED, Deprecated, "Deprecated")

//  NAMESPACES  //

namespace Talos::Reflect {

/// @brief Available Compile-Time Features.
$_XX_ENUM_CLASS(Feature, uint8_t, TALOS_XX_REFLECTION_FEATURES, INVALID = UINT8_MAX);

/// @brief Available Compile-Time Categories.
$_XX_ENUM_CLASS(Category, uint8_t, TALOS_XX_REFLECTION_CATEGORIES, INVALID = UINT8_MAX);

} // namespace Talos::Reflect

#endif
