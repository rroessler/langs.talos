#ifndef _FORGE_RESOURCE_SCHEME_HPP
#define _FORGE_RESOURCE_SCHEME_HPP

/// Forge Modules
#include "forge/forward/resource.hpp"

//  X-MACROS  //

#define FORGE_XX_RESOURCE_SCHEMES(X)      \
    X(HREF, $::URI::Scheme::HREF, false)  \
    X(SCRIPT, $::URI::Scheme::FILE, true) \
                                          \
    X(ARCHIVE, "arch", false)             \
    X(DYNAMIC, "dylib", true)             \
    X(INTERNAL, "talos", false)           \
    X(EXTERNAL, "crate", false)

//  NAMESPACES  //

namespace Forge::Resource {

    /// @brief Available Resource Schemes.
    $_XX_ENUM_CLASS(Scheme, uint8_t, FORGE_XX_RESOURCE_SCHEMES);

#define X(N, _, B, ...) (Scheme::N == S && B) ||
    template <Scheme S>
    concept Loadable = FORGE_XX_RESOURCE_SCHEMES(X) false;
#undef X

}  // namespace Forge::Resource

#endif
