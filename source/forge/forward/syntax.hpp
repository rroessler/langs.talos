#ifndef _FORGE_FORWARD_SYNTAX_HPP
#define _FORGE_FORWARD_SYNTAX_HPP

/// Vendor Modules
#include <xlsp/xlsp.hpp>

/// Forward Declarations
$_FWD(class Node, Forge::Syntax)
$_FWD(class Tree, Forge::Syntax)
$_FWD(class Preamble, Forge::Syntax)
$_FWD(struct Generator, Forge::Syntax)
$_FWD(class Identifier, Forge::Syntax)
$_FWD(class Declaration, Forge::Syntax)

/// Forward Defintiions
$_FWD(using Dependencies = std::vector<$::String::View>, Forge::Syntax)

#endif
