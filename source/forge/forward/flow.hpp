#ifndef _FORGE_FORWARD_FLOW_HPP
#define _FORGE_FORWARD_FLOW_HPP

/// Vendor Modules
#include <xlsp/xlsp.hpp>

/// Forward Declarations
$_FWD(class Control, Forge::Flow)
$_FWD(struct Passable, Forge::Flow)
$_FWD(class Unreachable, Forge::Flow)

/// Forward Definitions
$_FWD(using Branch = $::Functor::Unique<$::Ptr::Unique<Flow::Control>()>, Forge::Flow)

#endif
