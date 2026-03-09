#ifndef _TALOS_FORWARD_RELINT_HPP
#define _TALOS_FORWARD_RELINT_HPP

/// Vendor Modules
#include <xinv/xinv.hpp>

/// Talos Modules
#include "talos/forward/diagnostic.hpp"

/// Forward Declarations
$_FWD(Talos::Relint, struct Rule)
$_FWD(Talos::Relint, class Hooks)
$_FWD(Talos::Relint, class Mirror)
$_FWD(Talos::Relint, class Context)
$_FWD(Talos::Relint, class Service)
$_FWD(Talos::Relint, class Metadata)
$_FWD(Talos::Relint, struct Options)
$_FWD(Talos::Relint, struct Analyzer)

/// Forward Definitions
$_FWD(Talos::Relint, using Severity = Diagnostic::Severity)
$_FWD(Talos::Relint, using Deferrer = $::Functor::Unique<void(Analyzer*)>)
$_FWD(Talos::Relint, using Factory = $::Functor::Unique<void(Hooks*, const Rule*)>)

#endif
