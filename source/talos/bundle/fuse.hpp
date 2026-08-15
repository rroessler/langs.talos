#ifndef _TALOS_BUNDLE_FUSE_HPP
#define _TALOS_BUNDLE_FUSE_HPP

/// Talos Includes
#include "talos/forward/bundle.hpp"

/**
 * The fuses generated in this file should contain:
 * N: Name of the fuse (typically in uppercase).
 * F: A random hex-string (32-characters long).
 */

//  X-MACROS  //

#define TALOS_XX_FUSES_LIST(X) X(BUNDLED, "a8c0c5af64a6e91209ca2d3821c045ca")

//  NAMESPACES  //

namespace Talos::Fuse {

#define X(N, ...) extern XJCT::Sentinel::View N;
TALOS_XX_FUSES_LIST(X)
#undef X

} // namespace Talos::Fuse

#endif
