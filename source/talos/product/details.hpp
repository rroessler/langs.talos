#ifndef _TALOS_PRODUCT_DETAILS_HPP
#define _TALOS_PRODUCT_DETAILS_HPP

/// Talos Modules
#include "talos/product/version.hpp"
#include "talos/vendors/versions.hpp"

namespace Talos::Product {

    //  PUBLIC METHODS  //

    /// @brief Gets the executable version.
    static inline constexpr Version::Semantic version() {
        static auto s_version = Version::Semantic(TALOS_MM_VERSION);
        return s_version;  // and return the resulting version now
    }

    /// @brief Gets all the available vendors.
    static inline constexpr $::Record<Version::Semantic> vendors() {
#define X(N, V, ...) { N, Version::Semantic(V) },
        static $::Record<Version::Semantic> s_vendors = { TALOS_XX_VENDOR_VERSIONS(X) };
        return s_vendors;  // and return the result now
#undef X
    }

    /// @brief Gets the available scripts path.
    static inline constexpr $::Filesystem::Path scripts() {
        static auto s_parent = $::Path::canonical($::Executable::dirname() / ".." / "scripts");
        return s_parent;  // resolve the scripts location now
    }

}  // namespace Talos::Product

#endif
