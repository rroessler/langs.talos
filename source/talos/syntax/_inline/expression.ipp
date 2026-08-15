#ifndef _TALOS_SYNTAX_EXPRESSION_IPP
#define _TALOS_SYNTAX_EXPRESSION_IPP

/// Talos Includes
#include "talos/parser/dispatch.hpp"

/// Parser Includes
#include "talos/parser/_inline/macros.ipp"

/// Literal Includes
#include "talos/syntax/literal/boolean.hpp"
#include "talos/syntax/literal/identifier.hpp"
#include "talos/syntax/literal/lambda.hpp"
#include "talos/syntax/literal/numeric.hpp"
#include "talos/syntax/literal/record.hpp"
#include "talos/syntax/literal/text.hpp"
#include "talos/syntax/literal/tuple.hpp"
#include "talos/syntax/literal/void.hpp"

/// Expression Includes
#include "talos/syntax/expression/accessor.hpp"
#include "talos/syntax/expression/assign.hpp"
#include "talos/syntax/expression/binary.hpp"
#include "talos/syntax/expression/call.hpp"
#include "talos/syntax/expression/caret.hpp"
#include "talos/syntax/expression/cast.hpp"
#include "talos/syntax/expression/execute.hpp"
#include "talos/syntax/expression/group.hpp"
#include "talos/syntax/expression/infer.hpp"
#include "talos/syntax/expression/panic.hpp"
#include "talos/syntax/expression/ternary.hpp"
#include "talos/syntax/expression/typed.hpp"
#include "talos/syntax/expression/unary.hpp"

//  MACROS  //

/// @brief All available literal-expression nodes.
#define TALOS_XX_LITERAL_NODES(X) \
  X(Self)                         \
  X(Text)                         \
  X(Void)                         \
  X(True)                         \
  X(False)                        \
  X(Tuple)                        \
  X(Lambda)                       \
  X(Record)                       \
  X(Numeric)                      \
  X(Identifier)

/// @brief All available prefix-expression nodes.
#define TALOS_XX_PREFIX_NODES(X) \
  X(Unary)                       \
  X(Caret)                       \
  X(Group)                       \
  X(Panic)

/// @brief All available infix-expression nodes.
#define TALOS_XX_INFIX_NODES(X) \
  X(Binary)                     \
  X(Ternary)                    \
  X(Call)                       \
  X(Cast)                       \
  X(Infer)                      \
  X(Typed)                      \
  X(Assign)                     \
  X(Execute)                    \
  X(Accessor)

/// @brief All available expression nodes.
#define TALOS_XX_EXPRESSION_NODES(X) \
  TALOS_XX_LITERAL_NODES(X)          \
  TALOS_XX_PREFIX_NODES(X)           \
  TALOS_XX_INFIX_NODES(X)

//  SPECIALIZATIONS  //

#define X(N, ...) TALOS_MM_PARSE_PREFIX(N, , );
TALOS_XX_LITERAL_NODES(X)
TALOS_XX_PREFIX_NODES(X)
#undef X

#define X(N, ...) TALOS_MM_PARSE_INFIX(N, , , );
TALOS_XX_INFIX_NODES(X)
#undef X

#endif
