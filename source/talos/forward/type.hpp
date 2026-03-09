#ifndef _TALOS_FORWARD_TYPE_HPP
#define _TALOS_FORWARD_TYPE_HPP

/// Vendor Modules
#include <xinv/xinv.hpp>

/// Talos Modules
#include "talos/forward/flow.hpp"

/// Forward Declarations
$_FWD(Talos::Type, class Context)
$_FWD(Talos::Type, class Lattice)
$_FWD(Talos::Type, class Analyzer)
$_FWD(Talos::Type, struct Options)
$_FWD(Talos::Type, struct Deduction)
$_FWD(Talos::Type, struct Narrowing)

$_FWD(Talos::Type, struct Tagged)
$_FWD(Talos::Type, class Entity)
$_FWD(Talos::Type, class World)

$_FWD(Talos::Type, struct Any)
$_FWD(Talos::Type, struct None)
$_FWD(Talos::Type, struct Unset)
$_FWD(Talos::Type, struct Failure)

$_FWD(Talos::Type, class Generic)
$_FWD(Talos::Type, class Instance)
$_FWD(Talos::Type, class Protocol)
$_FWD(Talos::Type, class Parameter)
$_FWD(Talos::Type, class Prototype)
$_FWD(Talos::Type, class Transform)

/// Forward Definitions
$_FWD(Talos::Type, using Erased = $::Ptr::Shared<Tagged>)
$_FWD(Talos::Type, using Deferrer = $::Functor::Shared<void(Analyzer*)>)
$_FWD(Talos::Type, using Template = std::vector<$::Ptr::Shared<Parameter>>)
$_FWD(Talos::Type, using Branch = $::Functor::Unique<$::Ptr::Unique<Flow::Control>(Analyzer*)>)
$_FWD(Talos::Type, using Constraints = $::Ptr::Shared<$::Map<const Parameter*, Erased>>)

#endif
