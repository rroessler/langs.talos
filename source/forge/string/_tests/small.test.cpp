/// Vendor Modules
#include <forge/forge.hpp>
#include <testing/testing.hpp>

//  TEST CASES  //

TEST_CASE(constructor, runner) {
    static constexpr auto value = "abcdefg";
    auto string = Forge::String::Small(value);
    runner->asserts()->equal(string.view(), value);
};

TEST_CASE(default, runner) {
    auto empty = Forge::String::Small();
    runner->asserts()->equal(empty.view(), "");
};

TEST_CASE(validate, runner) {
    Forge::Value::Any value = Forge::String::Small();
    runner->asserts()->okay(value.is<Forge::String::Dynamic>());
};

//  TEST SECTIONS  //

TEST_SECTION(FORGE)->emplace({
    TEST_GROUP("Value/String",
        {
            TEST_BIND(constructor, "String::Small"),
            TEST_BIND(default, "String::Small"),
            TEST_BIND(validate, "String::Small"),
        }),
});
