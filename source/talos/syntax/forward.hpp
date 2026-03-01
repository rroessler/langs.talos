#ifndef _TALOS_SYNTAX_FORWARD_HPP
#define _TALOS_SYNTAX_FORWARD_HPP

/// Forge Modules
#include <forge/syntax/visitor.hpp>

#define X(N, ...) $_FWD(using N = Forge::Syntax::N, Talos::Syntax)
X(Node) FORGE_XX_SYNTAX_NODES(X)
#undef X

#endif
