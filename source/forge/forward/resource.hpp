#ifndef _FORGE_FORWARD_RESOURCE_HPP
#define _FORGE_FORWARD_RESOURCE_HPP

/// Vendor Modules
#include <xinv/xinv.hpp>
#include <xlsp/xlsp.hpp>

/// Forward Declarations
$_FWD(class Frame, Forge::Resource)
$_FWD(class Trace, Forge::Resource)
$_FWD(class Location, Forge::Resource)

/// Forward Definitions
$_FWD(using Stack = std::vector<Location>, Forge::Resource)

#endif
