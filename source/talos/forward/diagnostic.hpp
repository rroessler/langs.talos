#ifndef _TALOS_FORWARD_DIAGNOSTIC_HPP
#define _TALOS_FORWARD_DIAGNOSTIC_HPP

/// Vendor Includes
#include <xinv/xinv.hpp>
#include <xlsp/xlsp.hpp>

/// Forward Declarations
$_FWD(Talos::Diagnostic, class View)
$_FWD(Talos::Diagnostic, class Scope)
$_FWD(Talos::Diagnostic, class Reporter)
$_FWD(Talos::Diagnostic, struct Options)

/// Forward Definitions
$_FWD(Talos::Diagnostic, using Code = XLSP::Diagnostic::Code)
$_FWD(Talos::Diagnostic, using Severity = XLSP::Diagnostic::Severity)
$_FWD(Talos::Diagnostic, using Tags = $::Enum::Flags<XLSP::Diagnostic::Tag>)

$_FWD(Talos::Diagnostic, static constexpr auto Deprecated = XLSP::Diagnostic::Tag::DEPRECATED)
$_FWD(Talos::Diagnostic, static constexpr auto Unnecessary = XLSP::Diagnostic::Tag::UNNECESSARY)

#endif
