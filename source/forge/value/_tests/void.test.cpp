/// Vendor Modules
#include <forge/forge.hpp>
#include <testing/testing.hpp>

//  TEST CASES  //

TEST_CASE(default, runner) {
    auto value = Forge::Value::Void();
    runner->asserts()->okay(value.okay());
};

TEST_CASE(feedback, runner) {
    auto feedback = Forge::Value::Feedback::EXCEPTION_THROWN;
    auto value = Forge::Value::Void(feedback);  // prepare
    runner->asserts()->equal(value.feedback(), feedback);
    runner->asserts()->equal(value.traits().feedback(), feedback);
};

TEST_CASE(validate, runner) {
    Forge::Value::Any value = Forge::Value::Void();
    runner->asserts()->okay(value.is<Forge::Value::Void>());
};

//  TEST SECTIONS  //

TEST_SECTION(FORGE)->emplace({
    TEST_GROUP("Value/Boolean",
        {
            TEST_BIND(default, "Value::Void"),
            TEST_BIND(feedback, "Value::Void"),
            TEST_BIND(validate, "Value::Void"),
        }),
});
