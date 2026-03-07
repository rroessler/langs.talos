#ifndef _TALOS_FORWARD_RELINT_HPP
#define _TALOS_FORWARD_RELINT_HPP

/// Vendor Modules
#include <xinv/xinv.hpp>

/// Talos Modules
#include "talos/forward/diagnostic.hpp"

/// Forward Declarations
$_FWD(struct Rule, Talos::Relint)
$_FWD(class Hooks, Talos::Relint)
$_FWD(class Mirror, Talos::Relint)
$_FWD(class Context, Talos::Relint)
$_FWD(class Service, Talos::Relint)
$_FWD(class Metadata, Talos::Relint)
$_FWD(struct Options, Talos::Relint)
$_FWD(struct Analyzer, Talos::Relint)

/// Forward Definitions
$_FWD(using Severity = Diagnostic::Severity, Talos::Relint)
$_FWD(using Deferrer = $::Functor::Unique<void(Analyzer*)>, Talos::Relint)
$_FWD(using Factory = $::Functor::Unique<void(Hooks*, const Rule*)>, Talos::Relint)

#endif
