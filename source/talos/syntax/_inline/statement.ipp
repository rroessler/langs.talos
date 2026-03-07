#ifndef _TALOS_SYNTAX_STATEMENT_IPP
#define _TALOS_SYNTAX_STATEMENT_IPP

/// Talos Modules
#include "talos/parser/dispatch.hpp"

/// Statement Modules
#include "talos/syntax/statement/block.hpp"
#include "talos/syntax/statement/conditional.hpp"
#include "talos/syntax/statement/flow.hpp"
#include "talos/syntax/statement/import.hpp"
#include "talos/syntax/statement/loop.hpp"

//  MACROS  //

#define TALOS_XX_STATEMENT_NODES(X) \
    X(Break)                        \
    X(Return)                       \
    X(Continue)                     \
                                    \
    X(For)                          \
    X(Loop)                         \
    X(Block)                        \
    X(Conditional)                  \
                                    \
    X(Import)

//  SPECIALIZATIONS  //

#define X(N, ...) TALOS_MM_PARSE_STMT(N, );
TALOS_XX_STATEMENT_NODES(X)
#undef X

#endif
