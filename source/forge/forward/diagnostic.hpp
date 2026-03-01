#ifndef _FORGE_FORWARD_DIAGNOSTIC_HPP
#define _FORGE_FORWARD_DIAGNOSTIC_HPP

/// Forge Includes
#include "forge/forward/resource.hpp"

/// Forward Declarations
$_FWD(class View, Forge::Diagnostic)
$_FWD(class Scope, Forge::Diagnostic)
$_FWD(class Reporter, Forge::Diagnostic)
$_FWD(struct Options, Forge::Diagnostic)

/// Forward Definitions
$_FWD(using Code = XLSP::Diagnostic::Code, Forge::Diagnostic)
$_FWD(using Severity = XLSP::Diagnostic::Severity, Forge::Diagnostic)
$_FWD(using Tags = $::Enum::Flags<XLSP::Diagnostic::Tag>, Forge::Diagnostic)

$_FWD(static constexpr auto Deprecated = XLSP::Diagnostic::Tag::DEPRECATED, Forge::Diagnostic)
$_FWD(static constexpr auto Unnecessary = XLSP::Diagnostic::Tag::UNNECESSARY, Forge::Diagnostic)

#endif
