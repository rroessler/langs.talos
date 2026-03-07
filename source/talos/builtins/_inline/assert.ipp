#ifndef _TALOS_BUILTINS_ASSERT_IPP
#define _TALOS_BUILTINS_ASSERT_IPP

/// Talos Modules
#include "talos/number/math.hpp"
#include "talos/runtime/isolate.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/builtins.ipp"

//  MACROS  //

#define TALOS_MM_ASSERT_THAT(I, C, ...)                     \
    $_PP_BLOCK({                                            \
        if ($_UNLIKELY(!(C))) return I->panic(__VA_ARGS__); \
    })

#define TALOS_MM_ASSERT_ARGC(I, S, MIN, ...) TALOS_MM_ASSERT_THAT(I, S >= MIN, 6000251, MIN)
#define TALOS_MM_ASSERT_TYPEOF(I, T, V, ...) TALOS_MM_ASSERT_THAT(I, (V).is<T>(), 6000253, #V, #T)
#define TALOS_MM_ASSERT_INTEGRAL(I, V, ...) TALOS_MM_ASSERT_THAT(I, Number::Math::integral(V), 6000501)
#define TALOS_MM_ASSERT_INDEX(I, S, IDX, ...) TALOS_MM_ASSERT_THAT(I, (IDX >= 0) && (IDX < S), 3000701, S, IDX)
#define TALOS_MM_ASSERT_LOWER(I, V, MIN, ...) TALOS_MM_ASSERT_THAT(I, V >= MIN, 6000602, MIN)
#define TALOS_MM_ASSERT_UPPER(I, V, MAX, ...) TALOS_MM_ASSERT_THAT(I, V <= MAX, 6000601, MAX)
#define TALOS_MM_ASSERT_BOUNDS(I, V, MIN, MAX, ...) \
    TALOS_MM_ASSERT_LOWER(I, V, MIN);               \
    TALOS_MM_ASSERT_UPPER(I, V, MAX)

#endif
