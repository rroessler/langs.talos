#ifndef _TALOS_FORWARD_STRING_HPP
#define _TALOS_FORWARD_STRING_HPP

/// Vendor Modules
#include <xinv/xinv.hpp>

/// Forward Declarations
$_FWD(Talos::String, class Runes)
$_FWD(Talos::String, class Intern)
$_FWD(Talos::String, struct Small)
$_FWD(Talos::String, struct Large)
$_FWD(Talos::String, struct Dynamic)

/// Forward Definitions
$_FWD(Talos::String, using Arguments = fmt::dynamic_format_arg_store<fmt::format_context>)

#endif
