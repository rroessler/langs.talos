#ifndef _TALOS_FORWARD_FLOW_HPP
#define _TALOS_FORWARD_FLOW_HPP

/// Vendor Modules
#include <xlsp/xlsp.hpp>

/// Forward Declarations
$_FWD(class Control, Talos::Flow)
$_FWD(struct Passable, Talos::Flow)
$_FWD(class Unreachable, Talos::Flow)

/// Forward Definitions
$_FWD(using Branch = $::Functor::Unique<$::Ptr::Unique<Flow::Control>()>, Talos::Flow)

#endif
