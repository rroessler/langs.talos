#ifndef _TALOS_FORWARD_TYPE_HPP
#define _TALOS_FORWARD_TYPE_HPP

/// Vendor Modules
#include <xinv/xinv.hpp>

/// Talos Modules
#include "talos/forward/flow.hpp"

/// Forward Declarations
$_FWD(class Context, Talos::Type)
$_FWD(class Lattice, Talos::Type)
$_FWD(class Analyzer, Talos::Type)
$_FWD(struct Options, Talos::Type)
$_FWD(struct Deduction, Talos::Type)
$_FWD(struct Narrowing, Talos::Type)

$_FWD(struct Tagged, Talos::Type)
$_FWD(class Entity, Talos::Type)
$_FWD(class World, Talos::Type)

$_FWD(struct Any, Talos::Type)
$_FWD(struct None, Talos::Type)
$_FWD(struct Unset, Talos::Type)
$_FWD(struct Failure, Talos::Type)

$_FWD(class Generic, Talos::Type)
$_FWD(class Instance, Talos::Type)
$_FWD(class Protocol, Talos::Type)
$_FWD(class Parameter, Talos::Type)
$_FWD(class Prototype, Talos::Type)
$_FWD(class Transform, Talos::Type)

/// Forward Definitions
$_FWD(using Erased = $::Ptr::Shared<Tagged>, Talos::Type)
$_FWD(using Deferrer = $::Functor::Shared<void(Analyzer*)>, Talos::Type)
$_FWD(using Template = std::vector<$::Ptr::Shared<Parameter>>, Talos::Type)
$_FWD(using Branch = $::Functor::Unique<$::Ptr::Unique<Flow::Control>(Analyzer*)>, Talos::Type)
$_FWD(using Constraints = $::Ptr::Shared<$::Map<const Parameter * $_PP_COMMA Erased>>, Talos::Type)

#endif
