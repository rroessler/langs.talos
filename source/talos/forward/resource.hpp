#ifndef _TALOS_FORWARD_RESOURCE_HPP
#define _TALOS_FORWARD_RESOURCE_HPP

/// Vendor Modules
#include <xinv/xinv.hpp>
#include <xlsp/xlsp.hpp>

/// Forward Declarations
$_FWD(class Frame, Talos::Resource)
$_FWD(class Trace, Talos::Resource)
$_FWD(class Location, Talos::Resource)

/// Forward Definitions
$_FWD(using Stack = std::vector<Location>, Talos::Resource)

#endif
