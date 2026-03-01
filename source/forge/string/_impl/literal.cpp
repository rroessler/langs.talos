/// Forge Modules
#include "forge/string/literal.hpp"
#include "forge/function/arguments.hpp"
#include "forge/number/tagged.hpp"
#include "forge/runtime/isolate.hpp"

/// Forward Declarations
$_FWD(Value::Any report(Runtime::Isolate *, const std::exception &), Forge::String::Literal)
$_FWD(Value::Any report(Runtime::Isolate *, const $::String::View &), Forge::String::Literal)

//  PUBLIC METHODS  //

Forge::Value::Any Forge::String::Literal::style(
    Runtime::Isolate *isolate, String::Dynamic message, const Function::Arguments &args) {
    return style(isolate, message.view(), args);
}

Forge::Value::Any Forge::String::Literal::style(
    Runtime::Isolate *isolate, const $::String::View &message, const Function::Arguments &args) {
    // prepare a string-stream for conversion
    auto oss = $::String::Stream();

    // and construct the arguments to be used
    auto store = Arguments();
    store.reserve(args.size(), 0);

    // emplace each of the store values now
    for (const auto &value : args.span()) {
        if (value.is<Number::Tagged>()) store.push_back(value.as<Number::Tagged>().value());
        else oss << value, store.push_back(oss.str()), $::String::Stream().swap(oss);
    }

    // and finally request styling now
    return style(isolate, message, std::move(store));
}

Forge::Value::Any Forge::String::Literal::style(
    Runtime::Isolate *isolate, String::Dynamic message, Arguments &&arguments) {
    return style(isolate, message.view(), std::move(arguments));
}

Forge::Value::Any Forge::String::Literal::style(
    Runtime::Isolate *isolate, const $::String::View &message, Arguments &&arguments) {
    // clang-format off
    try { return Dynamic(isolate, fmt::vformat(message, std::move(arguments))); }
    catch (const std::exception &exception) { return report(isolate, exception); }
    // clang-format on
}

Forge::Value::Any Forge::String::Literal::report(Runtime::Isolate *isolate, const std::exception &exception) {
    return report(isolate, exception.what());
}

Forge::Value::Any Forge::String::Literal::report(Runtime::Isolate *isolate, const $::String::View &message) {
    return isolate->panic(6000403, $::Convert::capitalize(message));
}
