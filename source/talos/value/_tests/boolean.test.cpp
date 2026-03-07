/// Vendor Modules
#include <talos/talos.hpp>
#include <testing/testing.hpp>

//  TEST CASES  //

TEST_CASE(constructor, runner) {
    auto truthy = Talos::Value::Boolean(true);
    auto falsey = Talos::Value::Boolean(false);

    runner->asserts()->equal(truthy, true);
    runner->asserts()->equal(falsey, false);
};

TEST_CASE(default, runner) {
    auto value = Talos::Value::Boolean();
    runner->asserts()->equal(value, false);
};

TEST_CASE(validate, runner) {
    Talos::Value::Any value = Talos::Value::Boolean();
    runner->asserts()->okay(value.is<Talos::Value::Boolean>());
};

//  TEST SECTIONS  //

TEST_SECTION(TALOS)->emplace({
    TEST_GROUP("Value/Boolean",
        {
            TEST_BIND(constructor, "Value::Boolean"),
            TEST_BIND(default, "Value::Boolean"),
            TEST_BIND(validate, "Value::Boolean"),
        }),
});
