#ifndef _TALOS_FORWARD_BUNDLE_HPP
#define _TALOS_FORWARD_BUNDLE_HPP

/// Vendor Modules
#include <xjct/xjct.hpp>

/// Talos Modules
#include "talos/forward/runtime.hpp"

/// Forward Declarations
$_FWD(Talos::Bundle, class Archive)
$_FWD(Talos::Bundle, class Service)
$_FWD(Talos::Bundle, struct Options)

/// Forward Definitions
$_FWD(Talos::Bundle, using Blob = XJCT::Archive::Blob)
$_FWD(Talos::Bundle, using Buffer = XJCT::Archive::Buffer)
$_FWD(Talos::Bundle, using Executable = XJCT::Archive::Binary)

#endif
