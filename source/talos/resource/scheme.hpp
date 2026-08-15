#ifndef _TALOS_RESOURCE_RESOLVE_HPP
#define _TALOS_RESOURCE_RESOLVE_HPP

/// Talos Includes
#include "talos/forward/resource.hpp"

//  X-MACROS  //

/// @brief All available resource schemes.
#define TALOS_XX_RESOURCE_SCHEMES(X) \
  X(FILE, "file", true)              \
  X(HREF, "href", false)             \
  X(ARCH, "arch", false)             \
  X(DYLIB, "dylib", true)            \
  X(TALOS, "talos", false)           \
  X(CRATE, "crate", false)

//  NAMESPACES  //

namespace Talos::Resource {

//  TYPEDEFS  //

/// @brief Lookup Result Typing.
using Result = std::expected<$::URI::Buffer, $::String::Buffer>;

#define X(N, S, ...) $_FWD(Scheme, static constexpr $::String::Literal N = S)
// prepare the baseline schemes that we allow
TALOS_XX_RESOURCE_SCHEMES(X)

// ensure that some of the schemes have valid correlations
static_assert(Scheme::FILE == $::URI::Scheme::FILE);
static_assert(Scheme::HREF == $::URI::Scheme::HREF);
#undef X

} // namespace Talos::Resource

#endif
