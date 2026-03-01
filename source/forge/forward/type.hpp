#ifndef _FORGE_FORWARD_TYPE_HPP
#define _FORGE_FORWARD_TYPE_HPP

/// Vendor Modules
#include <xinv/xinv.hpp>

/// Forge Modules
#include "forge/forward/flow.hpp"

/// Forward Declarations
$_FWD(class Context, Forge::Type)
$_FWD(class Lattice, Forge::Type)
$_FWD(class Analyzer, Forge::Type)
$_FWD(struct Options, Forge::Type)
$_FWD(struct Deduction, Forge::Type)
$_FWD(struct Narrowing, Forge::Type)

$_FWD(struct Tagged, Forge::Type)
$_FWD(class Entity, Forge::Type)
$_FWD(class World, Forge::Type)

$_FWD(struct Any, Forge::Type)
$_FWD(struct None, Forge::Type)
$_FWD(struct Unset, Forge::Type)
$_FWD(struct Failure, Forge::Type)

$_FWD(class Generic, Forge::Type)
$_FWD(class Instance, Forge::Type)
$_FWD(class Protocol, Forge::Type)
$_FWD(class Parameter, Forge::Type)
$_FWD(class Prototype, Forge::Type)
$_FWD(class Transform, Forge::Type)

/// Forward Definitions
$_FWD(using Erased = $::Ptr::Shared<Tagged>, Forge::Type)
$_FWD(using Deferrer = $::Functor::Shared<void(Analyzer*)>, Forge::Type)
$_FWD(using Template = std::vector<$::Ptr::Shared<Parameter>>, Forge::Type)
$_FWD(using Branch = $::Functor::Unique<$::Ptr::Unique<Flow::Control>(Analyzer*)>, Forge::Type)
$_FWD(using Constraints = $::Ptr::Shared<$::Map<const Parameter * $_PP_COMMA Erased>>, Forge::Type)

#endif
