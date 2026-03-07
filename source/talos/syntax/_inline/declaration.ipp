#ifndef _TALOS_SYNTAX_DECLARATION_IPP
#define _TALOS_SYNTAX_DECLARATION_IPP

/// Talos Modules
#include "talos/parser/dispatch.hpp"
#include "talos/syntax/tree.hpp"

/// Declaration Modules
#include "talos/syntax/attribute/deprecated.hpp"
#include "talos/syntax/attribute/operator.hpp"
#include "talos/syntax/attribute/overload.hpp"
#include "talos/syntax/declaration/alias.hpp"
#include "talos/syntax/declaration/class.hpp"
#include "talos/syntax/declaration/enum.hpp"
#include "talos/syntax/declaration/namespace.hpp"
#include "talos/syntax/declaration/preamble.hpp"
#include "talos/syntax/declaration/variable.hpp"

//  MACROS  //

#define TALOS_XX_ANONYMOUS_NODES(X) \
    X(Tree)                         \
    X(Variant)                      \
    X(Decorator)                    \
                                    \
    X(Operator)                     \
    X(Overload)                     \
    X(Deprecated)

#define TALOS_XX_DECLARATION_NODES(X) \
    X(Enum)                           \
    X(Alias)                          \
    X(Class)                          \
    X(Variable)                       \
    X(Namespace)

//  SPECIALIZATIONS  //

#define X(N, ...) TALOS_MM_PARSE_DECL(N, );
X(Declaration)
TALOS_XX_ANONYMOUS_NODES(X)
TALOS_XX_DECLARATION_NODES(X)
#undef X

#endif
