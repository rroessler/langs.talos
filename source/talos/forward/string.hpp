#ifndef _TALOS_FORWARD_STRING_HPP
#define _TALOS_FORWARD_STRING_HPP

/// Vendor Modules
#include <xinv/xinv.hpp>

/// Forward Declarations
$_FWD(class Runes, Talos::String)
$_FWD(class Intern, Talos::String)
$_FWD(struct Small, Talos::String)
$_FWD(struct Large, Talos::String)
$_FWD(struct Dynamic, Talos::String)

/// Forward Definitions
$_FWD(using Arguments = fmt::dynamic_format_arg_store<fmt::format_context>, Talos::String)

#endif
