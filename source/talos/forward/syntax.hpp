#ifndef _TALOS_FORWARD_SYNTAX_HPP
#define _TALOS_FORWARD_SYNTAX_HPP

/// Vendor Modules
#include <xlsp/xlsp.hpp>

/// Forward Declarations
$_FWD(class Node, Talos::Syntax)
$_FWD(class Tree, Talos::Syntax)
$_FWD(class Preamble, Talos::Syntax)
$_FWD(struct Generator, Talos::Syntax)
$_FWD(class Identifier, Talos::Syntax)
$_FWD(class Declaration, Talos::Syntax)

/// Forward Defintiions
$_FWD(using Dependencies = std::vector<$::String::View>, Talos::Syntax)

#endif
