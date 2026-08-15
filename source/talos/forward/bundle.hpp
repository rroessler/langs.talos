#ifndef _TALOS_FORWARD_BUNDLE_HPP
#define _TALOS_FORWARD_BUNDLE_HPP

/// Vendor Includes
#include <xjct/xjct.hpp>

/// Talos Includes
#include "talos/forward/runtime.hpp"

/// Forward Declarations
$_FWD(Talos::Bundle, class Archive)
$_FWD(Talos::Bundle, struct Options)
$_FWD(Talos::Bundle, class Service)
$_FWD(Talos::Bundle, class Worker)
$_FWD(Talos::Bundle, struct Filesystem)

/// Forward Definitions
$_FWD(Talos::Bundle, using Provider = XJCT::Archive::Provider)
$_FWD(Talos::Bundle, using Executable = XJCT::Archive::Binary)

#endif
