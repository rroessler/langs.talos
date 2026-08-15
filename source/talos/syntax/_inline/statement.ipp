#ifndef _TALOS_SYNTAX_STATEMENT_IPP
#define _TALOS_SYNTAX_STATEMENT_IPP

/// Talos Includes
#include "talos/parser/dispatch.hpp"

/// Parser Includes
#include "talos/parser/_inline/macros.ipp"

/// Statement Includes
#include "talos/syntax/statement/block.hpp"
#include "talos/syntax/statement/break.hpp"
#include "talos/syntax/statement/conditional.hpp"
#include "talos/syntax/statement/continue.hpp"
#include "talos/syntax/statement/import.hpp"
#include "talos/syntax/statement/loop.hpp"
#include "talos/syntax/statement/match.hpp"
#include "talos/syntax/statement/return.hpp"

//  MACROS  //

/// @brief All available statement nodes.
#define TALOS_XX_STATEMENT_NODES(X) \
  X(Break)                          \
  X(Return)                         \
  X(Continue)                       \
                                    \
  X(For)                            \
  X(Loop)                           \
  X(Block)                          \
  X(Match)                          \
  X(Query)                          \
  X(Conditional)                    \
                                    \
  X(Import)

//  SPECIALIZATIONS  //

#define X(N, ...) TALOS_MM_PARSE_STMT(N, );
TALOS_XX_STATEMENT_NODES(X)
#undef X

#endif
