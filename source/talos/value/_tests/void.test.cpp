/// Vendor Modules
#include <talos/talos.hpp>
#include <testing/testing.hpp>

//  TEST CASES  //

TEST_CASE(default, runner) {
    auto value = Talos::Value::Void();
    runner->asserts()->okay(value.okay());
};

TEST_CASE(feedback, runner) {
    auto feedback = Talos::Value::Feedback::EXCEPTION_THROWN;
    auto value = Talos::Value::Void(feedback);  // prepare
    runner->asserts()->equal(value.feedback(), feedback);
    runner->asserts()->equal(value.traits().feedback(), feedback);
};

TEST_CASE(validate, runner) {
    Talos::Value::Any value = Talos::Value::Void();
    runner->asserts()->okay(value.is<Talos::Value::Void>());
};

//  TEST SECTIONS  //

TEST_SECTION(TALOS)->emplace({
    TEST_GROUP("Value/Boolean",
        {
            TEST_BIND(default, "Value::Void"),
            TEST_BIND(feedback, "Value::Void"),
            TEST_BIND(validate, "Value::Void"),
        }),
});
