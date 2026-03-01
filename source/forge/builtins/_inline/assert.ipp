#ifndef _FORGE_BUILTINS_ASSERT_IPP
#define _FORGE_BUILTINS_ASSERT_IPP

/// Forge Modules
#include "forge/number/math.hpp"
#include "forge/runtime/isolate.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/builtins.ipp"

//  MACROS  //

#define FORGE_MM_ASSERT_THAT(I, C, ...)                     \
    $_PP_BLOCK({                                            \
        if ($_UNLIKELY(!(C))) return I->panic(__VA_ARGS__); \
    })

#define FORGE_MM_ASSERT_ARGC(I, S, MIN, ...) FORGE_MM_ASSERT_THAT(I, S >= MIN, 6000251, MIN)
#define FORGE_MM_ASSERT_TYPEOF(I, T, V, ...) FORGE_MM_ASSERT_THAT(I, (V).is<T>(), 6000253, #V, #T)
#define FORGE_MM_ASSERT_INTEGRAL(I, V, ...) FORGE_MM_ASSERT_THAT(I, Number::Math::integral(V), 6000501)
#define FORGE_MM_ASSERT_INDEX(I, S, IDX, ...) FORGE_MM_ASSERT_THAT(I, (IDX >= 0) && (IDX < S), 3000701, S, IDX)
#define FORGE_MM_ASSERT_LOWER(I, V, MIN, ...) FORGE_MM_ASSERT_THAT(I, V >= MIN, 6000602, MIN)
#define FORGE_MM_ASSERT_UPPER(I, V, MAX, ...) FORGE_MM_ASSERT_THAT(I, V <= MAX, 6000601, MAX)
#define FORGE_MM_ASSERT_BOUNDS(I, V, MIN, MAX, ...) \
    FORGE_MM_ASSERT_LOWER(I, V, MIN);               \
    FORGE_MM_ASSERT_UPPER(I, V, MAX)

#endif
