#ifndef _TALOS_FORWARD_RELINT_HPP
#define _TALOS_FORWARD_RELINT_HPP

/// Vendor Includes
#include <xtdlib/xtdlib.hpp>

/// Talos Includes
#include "talos/forward/diagnostic.hpp"

/// Forward Declarations
$_FWD(Talos::Relint, struct Rule)
$_FWD(Talos::Relint, class Hooks)
$_FWD(Talos::Relint, class Mirror)
$_FWD(Talos::Relint, struct Options)
$_FWD(Talos::Relint, class Exports)
$_FWD(Talos::Relint, class Scope)
$_FWD(Talos::Relint, class Context)
$_FWD(Talos::Relint, class Comments)
$_FWD(Talos::Relint, struct Analyzer)
$_FWD(Talos::Relint, struct Definition)

/// Forward Definitions
$_FWD(Talos::Relint, using Severity = Diagnostic::Severity)
$_FWD(Talos::Relint, using Factory = $::Unique::Functor<void(Hooks *, const Rule *) const>)

#endif
