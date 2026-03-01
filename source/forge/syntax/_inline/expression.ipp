#ifndef _FORGE_SYNTAX_EXPRESSION_IPP
#define _FORGE_SYNTAX_EXPRESSION_IPP

/// Forge Modules
#include "forge/parser/dispatch.hpp"

/// Literal Modules
#include "forge/syntax/literal/boolean.hpp"
#include "forge/syntax/literal/identifier.hpp"
#include "forge/syntax/literal/lambda.hpp"
#include "forge/syntax/literal/numeric.hpp"
#include "forge/syntax/literal/record.hpp"
#include "forge/syntax/literal/text.hpp"
#include "forge/syntax/literal/tuple.hpp"
#include "forge/syntax/literal/void.hpp"

/// Expression Modules
#include "forge/syntax/expression/accessor.hpp"
#include "forge/syntax/expression/assign.hpp"
#include "forge/syntax/expression/binary.hpp"
#include "forge/syntax/expression/call.hpp"
#include "forge/syntax/expression/caret.hpp"
#include "forge/syntax/expression/cast.hpp"
#include "forge/syntax/expression/group.hpp"
#include "forge/syntax/expression/infer.hpp"
#include "forge/syntax/expression/panic.hpp"
#include "forge/syntax/expression/spawn.hpp"
#include "forge/syntax/expression/ternary.hpp"
#include "forge/syntax/expression/typed.hpp"
#include "forge/syntax/expression/unary.hpp"

//  MACROS  //

#define FORGE_XX_LITERAL_NODES(X) \
    X(Text)                       \
    X(Void)                       \
    X(True)                       \
    X(False)                      \
    X(Tuple)                      \
    X(Lambda)                     \
    X(Record)                     \
    X(Numeric)                    \
    X(Identifier)

#define FORGE_XX_PREFIX_NODES(X) \
    X(Caret)                     \
    X(Unary)                     \
    X(Group)                     \
    X(Panic)

#define FORGE_XX_INFIX_NODES(X) \
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

#define X(N, ...) FORGE_MM_PARSE_PREFIX(N, , );
FORGE_XX_LITERAL_NODES(X)
FORGE_XX_PREFIX_NODES(X)
#undef X

#define X(N, ...) FORGE_MM_PARSE_INFIX(N, , , );
FORGE_XX_INFIX_NODES(X)
#undef X

#endif
