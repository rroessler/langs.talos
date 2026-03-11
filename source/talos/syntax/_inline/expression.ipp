#ifndef _TALOS_SYNTAX_EXPRESSION_IPP
#define _TALOS_SYNTAX_EXPRESSION_IPP

/// Talos Modules
#include "talos/parser/dispatch.hpp"

/// Literal Modules
#include "talos/syntax/literal/boolean.hpp"
#include "talos/syntax/literal/identifier.hpp"
#include "talos/syntax/literal/lambda.hpp"
#include "talos/syntax/literal/numeric.hpp"
#include "talos/syntax/literal/record.hpp"
#include "talos/syntax/literal/text.hpp"
#include "talos/syntax/literal/tuple.hpp"
#include "talos/syntax/literal/void.hpp"

/// Expression Modules
#include "talos/syntax/expression/accessor.hpp"
#include "talos/syntax/expression/assign.hpp"
#include "talos/syntax/expression/binary.hpp"
#include "talos/syntax/expression/call.hpp"
#include "talos/syntax/expression/caret.hpp"
#include "talos/syntax/expression/cast.hpp"
#include "talos/syntax/expression/group.hpp"
#include "talos/syntax/expression/infer.hpp"
#include "talos/syntax/expression/panic.hpp"
#include "talos/syntax/expression/spawn.hpp"
#include "talos/syntax/expression/ternary.hpp"
#include "talos/syntax/expression/typed.hpp"
#include "talos/syntax/expression/unary.hpp"

//  MACROS  //

#define TALOS_XX_LITERAL_NODES(X) \
    X(Self)                       \
    X(Text)                       \
    X(Void)                       \
    X(True)                       \
    X(False)                      \
    X(Tuple)                      \
    X(Lambda)                     \
    X(Record)                     \
    X(Numeric)                    \
    X(Identifier)

#define TALOS_XX_PREFIX_NODES(X) \
    X(Caret)                     \
    X(Unary)                     \
    X(Group)                     \
    X(Panic)

#define TALOS_XX_INFIX_NODES(X) \
    X(Binary)                   \
    X(Ternary)                  \
    X(Call)                     \
    X(Cast)                     \
    X(Infer)                    \
    X(Typed)                    \
    X(Spawn)                    \
    X(Assign)                   \
    X(Accessor)

//  SPECIALIZATIONS  //

#define X(N, ...) TALOS_MM_PARSE_PREFIX(N, , );
TALOS_XX_LITERAL_NODES(X)
TALOS_XX_PREFIX_NODES(X)
#undef X

#define X(N, ...) TALOS_MM_PARSE_INFIX(N, , , );
TALOS_XX_INFIX_NODES(X)
#undef X

#endif
