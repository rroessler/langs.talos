#ifndef _TALOS_SYNTAX_DECLARATION_IPP
#define _TALOS_SYNTAX_DECLARATION_IPP

/// Talos Includes
#include "talos/parser/dispatch.hpp"

/// Parser Includes
#include "talos/parser/_inline/macros.ipp"

/// Attribute Includes
#include "talos/syntax/attribute/deprecated.hpp"
#include "talos/syntax/attribute/internal.hpp"
#include "talos/syntax/attribute/overload.hpp"
#include "talos/syntax/attribute/override.hpp"

/// Declaration Includes
#include "talos/syntax/declaration/alias.hpp"
#include "talos/syntax/declaration/class.hpp"
#include "talos/syntax/declaration/enum.hpp"
#include "talos/syntax/declaration/namespace.hpp"
#include "talos/syntax/declaration/preamble.hpp"
#include "talos/syntax/declaration/variable.hpp"

//  MACROS  //

/// @brief All available anonymous nodes.
#define TALOS_XX_ANONYMOUS_NODES(X) \
  X(Tree)                           \
  X(Header)                         \
  X(Variant)                        \
  X(Decorator)                      \
  X(Fallback)                       \
                                    \
  X(Internal)                       \
  X(Overload)                       \
  X(Override)                       \
  X(Deprecated)

/// @brief All available declaration nodes.
#define TALOS_XX_DECLARATION_NODES(X) \
  X(Enum)                             \
  X(Alias)                            \
  X(Class)                            \
  X(Variable)                         \
  X(Namespace)

//  SPECIALIZATIONS  //

#define X(N, ...) TALOS_MM_PARSE_DECL(N, );
X(Declaration)
TALOS_XX_ANONYMOUS_NODES(X)
TALOS_XX_DECLARATION_NODES(X)
#undef X

#endif
