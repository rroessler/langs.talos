#ifndef _FORGE_BUNDLE_FUSE_HPP
#define _FORGE_BUNDLE_FUSE_HPP

/// Forge Modules
#include "forge/forward/bundle.hpp"

/**
 * The fuses generated in this file should contain:
 * N: Name of the fuse (typically in uppercase).
 * F: A random hex-string (32-characters long).
 */

//  X-MACROS  //

#define FORGE_XX_FUSES_LIST(X) X(BUNDLED, "a8c0c5af64a6e91209ca2d3821c045ca")

//  NAMESPACES  //

namespace Forge::Fuse {

#define X(N, ...) extern XJCT::Sentinel::View N;
    FORGE_XX_FUSES_LIST(X)
#undef X

}  // namespace Forge::Fuse

#endif
