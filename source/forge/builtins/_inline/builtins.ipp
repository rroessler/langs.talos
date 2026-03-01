#ifndef _FORGE_BUILTINS_INLINE_IPP
#define _FORGE_BUILTINS_INLINE_IPP

/// Builtin Modules
#include "forge/builtins/boolean/traits.hpp"
#include "forge/builtins/class/traits.hpp"
#include "forge/builtins/enum/traits.hpp"
#include "forge/builtins/exception/traits.hpp"
#include "forge/builtins/function/traits.hpp"
#include "forge/builtins/future/traits.hpp"
#include "forge/builtins/iterator/traits.hpp"
#include "forge/builtins/list/traits.hpp"
#include "forge/builtins/number/traits.hpp"
#include "forge/builtins/object/traits.hpp"
#include "forge/builtins/result/traits.hpp"
#include "forge/builtins/string/traits.hpp"
#include "forge/builtins/symbol/traits.hpp"
#include "forge/builtins/void/traits.hpp"

/// Builtins Custom
#include "forge/builtins/debug/traits.hpp"
#include "forge/builtins/intrinsics/traits.hpp"
#include "forge/builtins/todo/traits.hpp"

//  X-MACROS  //

#define FORGE_XX_BUILTINS_CUSTOM(X) \
    X(Builtins::Custom::Todo)       \
    X(Builtins::Custom::Debug)      \
    X(Builtins::Custom::Intrinsics)

#define FORGE_XX_BUILTINS_LIST(X) \
    FORGE_XX_VALUES_LIST(X)       \
    FORGE_XX_BUILTINS_CUSTOM(X)

#endif
