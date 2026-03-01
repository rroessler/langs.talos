#ifndef _FORGE_FORWARD_BUNDLE_HPP
#define _FORGE_FORWARD_BUNDLE_HPP

/// Vendor Modules
#include <xjct/xjct.hpp>

/// Forge Modules
#include "forge/forward/runtime.hpp"

/// Forward Declarations
$_FWD(class Archive, Forge::Bundle)
$_FWD(class Service, Forge::Bundle)
$_FWD(struct Options, Forge::Bundle)

/// Forward Definitions
$_FWD(using Blob = XJCT::Archive::Blob, Forge::Bundle)
$_FWD(using Buffer = XJCT::Archive::Buffer, Forge::Bundle)
$_FWD(using Executable = XJCT::Archive::Binary, Forge::Bundle)

#endif
