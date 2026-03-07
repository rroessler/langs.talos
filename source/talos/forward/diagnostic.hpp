#ifndef _TALOS_FORWARD_DIAGNOSTIC_HPP
#define _TALOS_FORWARD_DIAGNOSTIC_HPP

/// Talos Includes
#include "talos/forward/resource.hpp"

/// Forward Declarations
$_FWD(class View, Talos::Diagnostic)
$_FWD(class Scope, Talos::Diagnostic)
$_FWD(class Reporter, Talos::Diagnostic)
$_FWD(struct Options, Talos::Diagnostic)

/// Forward Definitions
$_FWD(using Code = XLSP::Diagnostic::Code, Talos::Diagnostic)
$_FWD(using Severity = XLSP::Diagnostic::Severity, Talos::Diagnostic)
$_FWD(using Tags = $::Enum::Flags<XLSP::Diagnostic::Tag>, Talos::Diagnostic)

$_FWD(static constexpr auto Deprecated = XLSP::Diagnostic::Tag::DEPRECATED, Talos::Diagnostic)
$_FWD(static constexpr auto Unnecessary = XLSP::Diagnostic::Tag::UNNECESSARY, Talos::Diagnostic)

#endif
