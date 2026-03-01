#ifndef _FORGE_PRODUCT_DETAILS_HPP
#define _FORGE_PRODUCT_DETAILS_HPP

/// Forge Modules
#include "forge/product/version.hpp"
#include "forge/vendors/versions.hpp"

namespace Forge::Product {

    //  PUBLIC METHODS  //

    /// @brief Gets the executable version.
    static inline constexpr Version::Semantic version() {
        static auto s_version = Version::Semantic(FORGE_MM_VERSION);
        return s_version;  // and return the resulting version now
    }

    /// @brief Gets all the available vendors.
    static inline constexpr $::Record<Version::Semantic> vendors() {
#define X(N, V, ...) { N, Version::Semantic(V) },
        static $::Record<Version::Semantic> s_vendors = { FORGE_XX_VENDOR_VERSIONS(X) };
        return s_vendors;  // and return the result now
#undef X
    }

    /// @brief Gets the available scripts path.
    static inline constexpr $::Filesystem::Path scripts() {
        static auto s_parent = $::Path::canonical($::Executable::dirname() / ".." / "scripts");
        return s_parent;  // resolve the scripts location now
    }

}  // namespace Forge::Product

#endif
