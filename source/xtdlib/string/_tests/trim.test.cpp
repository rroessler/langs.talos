/// Vendor Modules
#include <testing/testing.hpp>

//  MACROS  //

#define TEST_COMMON(N, R)                     \
    R->asserts()->equal($::Trim::N(""), "");  \
    R->asserts()->equal($::Trim::N(" "), ""); \
    R->asserts()->equal($::Trim::N("abc"), "abc");

//  TEST CASES  //

TEST_CASE(both, runner) {
    TEST_COMMON(both, runner)  // bind the common handlers
    runner->asserts()->equal($::Trim::both(" abc"), "abc");
    runner->asserts()->equal($::Trim::both(" abc "), "abc");
};

TEST_CASE(leading, runner) {
    TEST_COMMON(leading, runner)  // bind the common handlers
    runner->asserts()->equal($::Trim::leading(" abc"), "abc");
    runner->asserts()->equal($::Trim::leading(" abc "), "abc ");
};

TEST_CASE(trailing, runner) {
    TEST_COMMON(trailing, runner)  // bind the common handlers
    runner->asserts()->equal($::Trim::trailing("abc "), "abc");
    runner->asserts()->equal($::Trim::trailing(" abc "), " abc");
};

//  TEST SECTIONS  //

TEST_SECTION(XTDLIB)->emplace({
    TEST_GROUP("String/Trim",
        {
            TEST_BIND(both, "String::View"),
            TEST_BIND(leading, "String::View"),
            TEST_BIND(trailing, "String::View"),
        }),
});
