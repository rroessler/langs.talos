#ifndef _TALOS_FORWARD_SYNTAX_HPP
#define _TALOS_FORWARD_SYNTAX_HPP

/// Vendor Includes
#include <xlsp/xlsp.hpp>

/// Forward Declarations
$_FWD(Talos::Syntax, class Node)
$_FWD(Talos::Syntax, class Tree)
$_FWD(Talos::Syntax, class Bounds)
$_FWD(Talos::Syntax, class Trivia)
$_FWD(Talos::Syntax, class Storage)
$_FWD(Talos::Syntax, struct Generator)

$_FWD(Talos::Syntax, struct Annotation)
$_FWD(Talos::Syntax, class Signature)
$_FWD(Talos::Syntax, struct Parameters)
$_FWD(Talos::Syntax, class Constructor)
$_FWD(Talos::Syntax, class Placeholder)

$_FWD(Talos::Syntax, class Preamble)
$_FWD(Talos::Syntax, class Declaration)
$_FWD(Talos::Syntax, struct Variable)
$_FWD(Talos::Syntax, class Attribute)
$_FWD(Talos::Syntax, class Decorator)

$_FWD(Talos::Syntax, struct Expression)
$_FWD(Talos::Syntax, class Identifier)

$_FWD(Talos::Syntax, struct Statement)
$_FWD(Talos::Syntax, struct Unterminated{})

/// Forward Definitions
$_FWD(Talos::Syntax, using Template = std::vector<Placeholder *>)
$_FWD(Talos::Syntax, using Specialization = std::vector<Annotation *>)
$_FWD(Talos::Syntax, using Dependencies = std::vector<$::String::View>)

#endif
