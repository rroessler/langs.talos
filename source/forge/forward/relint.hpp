#ifndef _FORGE_FORWARD_RELINT_HPP
#define _FORGE_FORWARD_RELINT_HPP

/// Vendor Modules
#include <xinv/xinv.hpp>

/// Forge Modules
#include "forge/forward/diagnostic.hpp"

/// Forward Declarations
$_FWD(struct Rule, Forge::Relint)
$_FWD(class Hooks, Forge::Relint)
$_FWD(class Mirror, Forge::Relint)
$_FWD(class Context, Forge::Relint)
$_FWD(class Service, Forge::Relint)
$_FWD(class Metadata, Forge::Relint)
$_FWD(struct Options, Forge::Relint)
$_FWD(struct Analyzer, Forge::Relint)

/// Forward Definitions
$_FWD(using Severity = Diagnostic::Severity, Forge::Relint)
$_FWD(using Deferrer = $::Functor::Unique<void(Analyzer*)>, Forge::Relint)
$_FWD(using Factory = $::Functor::Unique<void(Hooks*, const Rule*)>, Forge::Relint)

#endif
