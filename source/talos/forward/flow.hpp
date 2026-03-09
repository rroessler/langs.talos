#ifndef _TALOS_FORWARD_FLOW_HPP
#define _TALOS_FORWARD_FLOW_HPP

/// Vendor Modules
#include <xlsp/xlsp.hpp>

/// Forward Declarations
$_FWD(Talos::Flow, class Control)
$_FWD(Talos::Flow, struct Passable)
$_FWD(Talos::Flow, class Unreachable)

/// Forward Definitions
$_FWD(Talos::Flow, using Branch = $::Functor::Unique<$::Ptr::Unique<Flow::Control>()>)

#endif
