#ifndef _TALOS_FORWARD_BUNDLE_HPP
#define _TALOS_FORWARD_BUNDLE_HPP

/// Vendor Modules
#include <xjct/xjct.hpp>

/// Talos Modules
#include "talos/forward/runtime.hpp"

/// Forward Declarations
$_FWD(class Archive, Talos::Bundle)
$_FWD(class Service, Talos::Bundle)
$_FWD(struct Options, Talos::Bundle)

/// Forward Definitions
$_FWD(using Blob = XJCT::Archive::Blob, Talos::Bundle)
$_FWD(using Buffer = XJCT::Archive::Buffer, Talos::Bundle)
$_FWD(using Executable = XJCT::Archive::Binary, Talos::Bundle)

#endif
