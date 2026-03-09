#ifndef _TALOS_FORWARD_SYNTAX_HPP
#define _TALOS_FORWARD_SYNTAX_HPP

/// Vendor Modules
#include <xlsp/xlsp.hpp>

/// Forward Declarations
$_FWD(Talos::Syntax, class Node)
$_FWD(Talos::Syntax, class Tree)
$_FWD(Talos::Syntax, class Preamble)
$_FWD(Talos::Syntax, struct Generator)
$_FWD(Talos::Syntax, class Identifier)
$_FWD(Talos::Syntax, class Declaration)

/// Forward Defintiions
$_FWD(Talos::Syntax, using Dependencies = std::vector<$::String::View>)

#endif
