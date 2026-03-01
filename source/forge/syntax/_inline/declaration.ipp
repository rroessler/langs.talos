#ifndef _FORGE_SYNTAX_DECLARATION_IPP
#define _FORGE_SYNTAX_DECLARATION_IPP

/// Forge Modules
#include "forge/parser/dispatch.hpp"
#include "forge/syntax/tree.hpp"

/// Declaration Modules
#include "forge/syntax/attribute/deprecated.hpp"
#include "forge/syntax/attribute/operator.hpp"
#include "forge/syntax/attribute/overload.hpp"
#include "forge/syntax/declaration/alias.hpp"
#include "forge/syntax/declaration/class.hpp"
#include "forge/syntax/declaration/enum.hpp"
#include "forge/syntax/declaration/namespace.hpp"
#include "forge/syntax/declaration/preamble.hpp"
#include "forge/syntax/declaration/variable.hpp"

//  MACROS  //

#define FORGE_XX_ANONYMOUS_NODES(X) \
    X(Tree)                         \
    X(Variant)                      \
    X(Decorator)                    \
                                    \
    X(Operator)                     \
    X(Overload)                     \
    X(Deprecated)

#define FORGE_XX_DECLARATION_NODES(X) \
    X(Enum)                           \
    X(Alias)                          \
    X(Class)                          \
    X(Variable)                       \
    X(Namespace)

//  SPECIALIZATIONS  //

#define X(N, ...) FORGE_MM_PARSE_DECL(N, );
X(Declaration)
FORGE_XX_ANONYMOUS_NODES(X)
FORGE_XX_DECLARATION_NODES(X)
#undef X

#endif
