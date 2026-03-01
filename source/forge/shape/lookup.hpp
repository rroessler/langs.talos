#ifndef _FORGE_SHAPE_LOOKUP_HPP
#define _FORGE_SHAPE_LOOKUP_HPP

/// Forge Modules
#include "forge/shape/limits.hpp"

//  X-MACROS  //

#define XX_VALUES_BYPASS(X)           \
    X(String::Small, String::Dynamic) \
    X(String::Large, String::Dynamic)

//  NAMESPACES  //

namespace Forge::Shape {

    /// @brief Invalid shape value.
    static constexpr auto Invalid = Limits::MAXIMUM;

    /// @brief Handles looking up associated shapes for values.
    template <class T>
    static constexpr uint32_t Lookup() {
#define X(D, B, ...) \
    if constexpr (std::same_as<T, D>) return Lookup<B>();
        XX_VALUES_BYPASS(X)
#undef X

        // prepare an initial threshold to be used now
        uint32_t shape = Limits::THRESHOLD;

#define X(T, ...) \
    case $::RTTI::Hash<T>(): --shape; $_FALLTHROUGH;
        switch ($::RTTI::Hash<T>()) {
            FORGE_XX_VALUES_IMMEDIATE(X)
            FORGE_XX_VALUES_OBJECT(X)
            X(Object::Instance)
            default: break;
        }
#undef X

        // and resolve as necessary now
        return shape == Limits::THRESHOLD ? Invalid : shape;
    }

}  // namespace Forge::Shape

#endif
