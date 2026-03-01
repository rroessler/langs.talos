/// Forge Modules
#include <forge/async/service.hpp>
#include <forge/member/factory.hpp>
#include <forge/testing/registry.hpp>

/// Assert Modules
#include <forge/builtins/_inline/assert.ipp>

/// Crate Modules
#include "crates/test/source/module.hpp"

//  PROPERTIES  //

/// @brief The underlying testing addon installer.
FORGE_MM_DYLIB_ADDON(Test, CRATE_XX_TEST_METHODS)

//  PRIVATE METHODS  //

FORGE_MM_DYLIB_METHOD(Test, case, isolate, args) {
    // ensure testing is enabled before continuing
    if (!m_enabled(isolate)) return Value::Void();

    FORGE_MM_ASSERT_ARGC(isolate, args.size(), 1);  // get named
    FORGE_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args[0]);

    // register without modifiers and return now
    return m_register(isolate, args), Value::Void();
}

FORGE_MM_DYLIB_METHOD(Test, skip, isolate, args) {
    // ensure testing is enabled before continuing
    if (!m_enabled(isolate)) return Value::Void();

    FORGE_MM_ASSERT_ARGC(isolate, args.size(), 1);  // get named
    FORGE_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args[0]);

    // register with the "skip" modifier now
    return m_register(isolate, args)->skip(true), Value::Void();
}

FORGE_MM_DYLIB_METHOD(Test, todo, isolate, args) {
    // ensure testing is enabled before continuing
    if (!m_enabled(isolate)) return Value::Void();

    FORGE_MM_ASSERT_ARGC(isolate, args.size(), 1);  // get named
    FORGE_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args[0]);

    // register with the "todo" modifier now
    return m_register(isolate, args)->todo(true), Value::Void();
}

FORGE_MM_DYLIB_METHOD(Test, bench, isolate, args) {
    // ensure testing is enabled before continuing
    if (!m_enabled(isolate)) return Value::Void();

    FORGE_MM_ASSERT_ARGC(isolate, args.size(), 1);  // get named
    FORGE_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args[0]);

    // prepare the arguments to be used now
    auto name = $::String::Buffer(args.at<String::Dynamic>(0).view());
    auto callback = args.at<Function::Dynamic>(1, Function::Dynamic());

    // get the underlying testing registry
    auto *registry = isolate->service<Testing::Registry>();
    registry->bench(name, m_callback(callback), m_location(isolate));

    // and declare a success on completion now
    return Value::Void();
}

FORGE_MM_DYLIB_METHOD(Test, suite, isolate, args) {
    // ensure testing is enabled before continuing
    if (!m_enabled(isolate)) return Value::Void();

    FORGE_MM_ASSERT_ARGC(isolate, args.size(), 1);  // get named
    FORGE_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args[0]);

    // prepare the arguments to be used now
    auto name = $::String::Buffer(args.at<String::Dynamic>(0).view());
    auto callback = args.at<Function::Dynamic>(1, Function::Dynamic());

    // get the underlying testing registry
    auto *registry = isolate->service<Testing::Registry>();
    auto *group = registry->group(name, m_location(isolate));

    // bind the setup handler for the group
    group->bind(m_callback(callback, group));

    // and declare a success on completion
    return Value::Void();
}

bool Forge::Package::Test::m_enabled(Runtime::Isolate *isolate) {
    return isolate->service<XI::Container>()->exists<Testing::Registry>();
}

Forge::Testing::Case *Forge::Package::Test::m_register(Runtime::Isolate *isolate, const Function::Arguments &args) {
    // prepare the arguments to be used now
    auto name = $::String::Buffer(args.at<String::Dynamic>(0).view());
    auto callback = args.at<Function::Dynamic>(1, Function::Dynamic());

    // get the underlying testing registry
    auto *registry = isolate->service<Testing::Registry>();

    // return the underlying test that was registered now
    return registry->test(name, m_callback(callback), m_location(isolate));
}

Forge::Testing::Callback Forge::Package::Test::m_callback(const Function::Dynamic &callback) {
    if (callback.nptr()) return [](Testing::Runner *) {};  // invalid callback
    return [callback](Testing::Runner *runner) { m_callback(runner, callback); };
}

Forge::Testing::Callback Forge::Package::Test::m_callback(const Function::Dynamic &callback, Testing::Group *group) {
    if (callback.nptr()) return [](Testing::Runner *) {};
    return [callback, group](Testing::Runner *runner) {
        auto *registry = runner->service<Testing::Registry>();
        $_UNUSED $_AUTO = registry->target(group);

        // race the incoming result now
        auto result = m_race(runner, callback);
        if (result.has_value()) return;  // valid

        // prepare the incoming exception now
        auto exception = result.error().as<Object::Exception>();
        auto message = $::String::Buffer(exception.message().view());
        runner->asserts()->fail(message, Testing::Traits::location(exception, false));

        // otherwise we want to safely fail now
        throw std::runtime_error(message);
    };
}

void Forge::Package::Test::m_callback(Testing::Runner *runner, const Function::Dynamic &callback) {
    // race the incoming result now
    auto result = m_race(runner, callback);
    if (result.has_value()) return;

    // handle incoming panics as failed assertions
    auto exception = result.error().as<Object::Exception>();
    auto location = Testing::Traits::location(exception, false);
    runner->asserts()->fail(exception.message().view(), location);
}

Forge::Async::Result Forge::Package::Test::m_race(Testing::Runner *runner, const Function::Dynamic &callback) {
    // get the underlying async service
    auto *async = runner->service<Async::Service>();

    // prepare the baseline isolate instance now
    auto *isolate = async->isolate();
    auto *thread = isolate->thread();

    // ensure we instance the future to be called
    auto future = isolate->create<Async::Future>(callback);

    // prepare some details for out timer and future
    auto duration = runner->options()->bench.timeout;

    // attempt waiting for the future to complete now
    auto result = future.timeout(thread, duration);

    // check if the result timed out at all now
    auto ignore = result.has_value() || result.error() != Value::Timeout();

    // handle incoming timeouts if necessary to do so now
    return ignore ? result : throw XT::Assert::Timeout();
}

XT::Location Forge::Package::Test::m_location(Runtime::Isolate *isolate) {
    return m_location(isolate->frame()->parent());  // always use the parent
}

XT::Location Forge::Package::Test::m_location(const Engine::Frame *frame) {
    return $_ASSERT(frame, "Invalid isolate frame"), m_location(frame->backtrace());
}

XT::Location Forge::Package::Test::m_location(const Resource::Trace &backtrace) {
    return Testing::Traits::location(backtrace);
}
