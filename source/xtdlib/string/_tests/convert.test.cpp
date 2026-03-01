/// Vendor Modules
#include <testing/testing.hpp>

//  TEST CASES  //

TEST_CASE(stringify, runner) {
    runner->asserts()->equal($::Convert::stringify(42), "42");
    runner->asserts()->equal($::Convert::stringify(true), "true");
};

TEST_CASE(lowercase, runner) {
    runner->asserts()->equal($::Convert::lowercase("ABC"), "abc");
    runner->asserts()->equal($::Convert::lowercase("123"), "123");
};

TEST_CASE(uppercase, runner) {
    runner->asserts()->equal($::Convert::uppercase("abc"), "ABC");
    runner->asserts()->equal($::Convert::uppercase("123"), "123");
};

TEST_CASE(capitalize, runner) {
    runner->asserts()->equal($::Convert::capitalize("hello"), "Hello");
    runner->asserts()->equal($::Convert::uppercase("123"), "123");
};

//  TEST SECTIONS  //

TEST_SECTION(XTDLIB)->emplace({
    TEST_GROUP("String/Convert",
        {
            TEST_BIND(stringify, "T"),
            TEST_BIND(lowercase, "String::View"),
            TEST_BIND(uppercase, "String::View"),
            TEST_BIND(capitalize, "String::View"),
        }),
});
