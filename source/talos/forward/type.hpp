#ifndef _TALOS_FORWARD_TYPE_HPP
#define _TALOS_FORWARD_TYPE_HPP

/// Vendor Includes
#include <xinv/xinv.hpp>

/// Talos Includes
#include "talos/forward/flow.hpp"
#include "talos/operator/kind.hpp"

/// Forward Declarations
$_FWD(Talos::Type, class Exports)
$_FWD(Talos::Type, class Analyzer)
$_FWD(Talos::Type, struct Match)
$_FWD(Talos::Type, struct Deduction)
$_FWD(Talos::Type, struct Narrowing)

$_FWD(Talos::Type, struct New)
$_FWD(Talos::Type, struct Unit)
$_FWD(Talos::Type, class Entity)
$_FWD(Talos::Type, class World)

$_FWD(Talos::Type, struct Any)
$_FWD(Talos::Type, struct None)
$_FWD(Talos::Type, struct Unset)
$_FWD(Talos::Type, struct Poison)

$_FWD(Talos::Type, class Callable)
$_FWD(Talos::Type, class Instance)
$_FWD(Talos::Type, class Structure)
$_FWD(Talos::Type, class Prototype)
$_FWD(Talos::Type, class Generic)
$_FWD(Talos::Type, class Parameter)
$_FWD(Talos::Type, class Transform)

/// Forward Definitions
$_FWD(Talos::Type, using Erased = $::Shared::Pointer<Unit>)
$_FWD(Talos::Type, using Control = $::Unique::Pointer<Flow::Control>)
$_FWD(Talos::Type, using Deferrer = $::Shared::Functor<void(Analyzer *)>)
$_FWD(Talos::Type, using Branch = $::Unique::Functor<Control(Analyzer *)>)
$_FWD(Talos::Type, using Constraints = $::Map::Base<const Parameter *, Erased>)
$_FWD(Talos::Type, using Template = std::vector<$::Shared::Pointer<Parameter>>)
$_FWD(Talos::Type, using Resolver = $::Shared::Functor<Erased(const Erased &, Constraints *) const>)
$_FWD(Talos::Type, using Apply = $::Shared::Functor<Erased(const Structure *, Operator::Kind, const Erased &) const>)

#endif
