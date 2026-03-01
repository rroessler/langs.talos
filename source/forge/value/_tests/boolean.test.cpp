/// Vendor Modules
#include <forge/forge.hpp>
#include <testing/testing.hpp>

//  TEST CASES  //

TEST_CASE(constructor, runner) {
    auto truthy = Forge::Value::Boolean(true);
    auto falsey = Forge::Value::Boolean(false);

    runner->asserts()->equal(truthy, true);
    runner->asserts()->equal(falsey, false);
};

TEST_CASE(default, runner) {
    auto value = Forge::Value::Boolean();
    runner->asserts()->equal(value, false);
};

TEST_CASE(validate, runner) {
    Forge::Value::Any value = Forge::Value::Boolean();
    runner->asserts()->okay(value.is<Forge::Value::Boolean>());
};

//  TEST SECTIONS  //

TEST_SECTION(FORGE)->emplace({
    TEST_GROUP("Value/Boolean",
        {
            TEST_BIND(constructor, "Value::Boolean"),
            TEST_BIND(default, "Value::Boolean"),
            TEST_BIND(validate, "Value::Boolean"),
        }),
});
