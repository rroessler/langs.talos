/// Forge Modules
#include <forge/member/factory.hpp>
#include <forge/testing/traits.hpp>

/// Assert Modules
#include <forge/builtins/_inline/assert.ipp>

/// Crate Modules
#include "crates/assert/source/module.hpp"

//  PROPERTIES  //

/// @brief The underlying assertion addon installer.
FORGE_MM_DYLIB_ADDON(Assert, CRATE_XX_ASSERT_METHODS)

/// @brief Explicit failed string.
static Forge::Value::Any g_failed = Forge::String::Small("Failed");

//  PRIVATE METHODS  //

FORGE_MM_DYLIB_METHOD(Assert, fail, isolate, args) { return m_panic(isolate, 7000000, args.at(0, g_failed)); }
FORGE_MM_DYLIB_METHOD(Assert, okay, isolate, args) { return m_test(isolate, args, true, "okay"); }
FORGE_MM_DYLIB_METHOD(Assert, truthy, isolate, args) { return m_test(isolate, args, true, "falsey"); }
FORGE_MM_DYLIB_METHOD(Assert, falsey, isolate, args) { return m_test(isolate, args, false, "truthy"); }

FORGE_MM_DYLIB_METHOD(Assert, exists, isolate, args) {
    // ensure we immediately fail if there are no arguments
    if (args.empty()) return isolate->panic(7000002, "exists");

    // ensure that the value is void now
    if (!args.at(0).is<Value::Void>()) return Value::Void();

    // get the incoming message to be shown now
    auto message = args.at<Value::Any>(1, Value::Void());

    // otherwise we resolve a suitable error message
    if (message.is<String::Dynamic>()) return m_panic(isolate, 7000000, message);
    return m_panic(isolate, 7000001, Value::Void().type_name());  // give reason
}

FORGE_MM_DYLIB_METHOD(Assert, equals, isolate, args) {
    // ensure we have the correct number of arguments
    FORGE_MM_ASSERT_ARGC(isolate, args.size(), 2);

    // validate the incoming arguments now
    auto actual = args.at(0), expected = args.at(1);
    if (actual == expected) return Value::Void();

    // check against string-based comparisons now
    if (actual.is<String::Dynamic>() && expected.is<String::Dynamic>()) {
        if (actual.as<String::Dynamic>().compare(expected.as<String::Dynamic>()) == 0) return Value::Void();
    }

    // get the incoming message to be shown now
    auto message = args.at<Value::Any>(2, Value::Void());

    // otherwise we resolve a suitable error message
    return message.is<String::Dynamic>() ? m_panic(isolate, 7000000, message) : m_panic(isolate, 7000003);
}

FORGE_MM_DYLIB_METHOD(Assert, differs, isolate, args) {
    // ensure we have the correct number of arguments
    FORGE_MM_ASSERT_ARGC(isolate, args.size(), 2);

    // validate the incoming arguments now
    auto actual = args.at(0), expected = args.at(1);
    if (actual != expected) return Value::Void();

    // check against string-based comparisons now
    if (actual.is<String::Dynamic>() && expected.is<String::Dynamic>()) {
        if (actual.as<String::Dynamic>().compare(expected.as<String::Dynamic>()) != 0) return Value::Void();
    }

    // get the incoming message to be shown now
    auto message = args.at<Value::Any>(2, Value::Void());

    // otherwise we resolve a suitable error message
    return message.is<String::Dynamic>() ? m_panic(isolate, 7000000, message) : m_panic(isolate, 7000004);
}

FORGE_MM_DYLIB_METHOD(Assert, panics, isolate, args) {
    // ensure we immediately fail if there are no arguments
    if (args.empty()) return isolate->panic(7000002, "exists");

    // ensure the leading argument is a function
    FORGE_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args[0]);

    // get the incoming function to be called now
    auto result = isolate->spawn(args.at(0));

    // if the result is an error, then stop
    if (!result.has_value()) return Value::Void();

    // get the incoming message to be shown now
    auto message = args.at<Value::Any>(1, Value::Void());

    // otherwise we resolve a suitable error message for when no panic occurs
    return message.is<String::Dynamic>() ? m_panic(isolate, 7000000, message) : m_panic(isolate, 7000005);
}

FORGE_MM_DYLIB_METHOD(Assert, test, isolate, args, bool state, const $::String::View &method) {
    // fail if there are no arguments given at all
    if (args.empty()) return isolate->panic(7000002, method);

    // ensure that the truthiness is valid now
    if (args.at(0).truthiness() == state) return Value::Void();

    // get the incoming message to be shown now
    auto message = args.at<Value::Any>(1, Value::Void());

    // otherwise we resolve a suitable error message
    if (message.is<String::Dynamic>()) return m_panic(isolate, 7000000, message);
    return m_panic(isolate, 7000001, state ? "truthy" : "falsey");  // give reason
}

Forge::Value::Any Forge::Package::Assert::m_panic(Runtime::Isolate *isolate, Object::Exception exception) {
    auto *services = isolate->service<XI::Container>();
    auto *session = services->when<Testing::Session>();
    if (session == nullptr) return isolate->panic(exception);

    // prepare the baseline reason and details
    auto because = exception.message().view();
    auto location = Testing::Traits::location(exception);

    // prepare the reporter to be used now
    session->runner()->asserts()->fail(because, location);

    // and emit that no error occured here
    return Value::Void();
}
