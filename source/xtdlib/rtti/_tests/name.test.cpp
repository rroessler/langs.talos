/// Vendor Modules
#include <testing/testing.hpp>

/// Forward Declarations
$_FWD(Mock, struct A)
$_FWD(Mock::B, struct C)
$_FWD(Mock, template <class> struct D)

//  X-MACROS  //

#define XX_TESTS(X)       \
    X(single, Mock::A)    \
    X(nested, Mock::B::C) \
    X(templated, Mock::D<Mock::A>)

//  TEST CASES  //

#define X(N, T, ...) \
    TEST_CASE(N, runner) { runner->asserts()->equal($::RTTI::Name::of<T>(), #T); };
XX_TESTS(X)
#undef X

//  TEST SECTIONS  //

#define X(N, ...) TEST_BIND(N, "T"),
TEST_SECTION(XTDLIB)->emplace({
    TEST_GROUP("RTTI/Name", { XX_TESTS(X) }),
});
#undef X
