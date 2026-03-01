#ifndef _FORGE_SYNTAX_STATEMENT_IPP
#define _FORGE_SYNTAX_STATEMENT_IPP

/// Forge Modules
#include "forge/parser/dispatch.hpp"

/// Statement Modules
#include "forge/syntax/statement/block.hpp"
#include "forge/syntax/statement/conditional.hpp"
#include "forge/syntax/statement/flow.hpp"
#include "forge/syntax/statement/import.hpp"
#include "forge/syntax/statement/loop.hpp"

//  MACROS  //

#define FORGE_XX_STATEMENT_NODES(X) \
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

#define X(N, ...) FORGE_MM_PARSE_STMT(N, );
FORGE_XX_STATEMENT_NODES(X)
#undef X

#endif
