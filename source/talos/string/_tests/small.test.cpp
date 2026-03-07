/// Vendor Modules
#include <talos/talos.hpp>
#include <testing/testing.hpp>

//  TEST CASES  //

TEST_CASE(constructor, runner) {
    static constexpr auto value = "abcdefg";
    auto string = Talos::String::Small(value);
    runner->asserts()->equal(string.view(), value);
};

TEST_CASE(default, runner) {
    auto empty = Talos::String::Small();
    runner->asserts()->equal(empty.view(), "");
};

TEST_CASE(validate, runner) {
    Talos::Value::Any value = Talos::String::Small();
    runner->asserts()->okay(value.is<Talos::String::Dynamic>());
};

//  TEST SECTIONS  //

TEST_SECTION(TALOS)->emplace({
    TEST_GROUP("Value/String",
        {
            TEST_BIND(constructor, "String::Small"),
            TEST_BIND(default, "String::Small"),
            TEST_BIND(validate, "String::Small"),
        }),
});
