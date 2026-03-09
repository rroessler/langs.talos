/// Talos Modules
#include "talos/string/literal.hpp"
#include "talos/function/arguments.hpp"
#include "talos/number/tagged.hpp"
#include "talos/runtime/isolate.hpp"

/// Forward Declarations
$_FWD(Talos::String::Literal, Value::Any report(Runtime::Isolate *, const std::exception &))
$_FWD(Talos::String::Literal, Value::Any report(Runtime::Isolate *, const $::String::View &))

//  PUBLIC METHODS  //

Talos::Value::Any Talos::String::Literal::style(
    Runtime::Isolate *isolate, String::Dynamic message, const Function::Arguments &args) {
    return style(isolate, message.view(), args);
}

Talos::Value::Any Talos::String::Literal::style(
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

Talos::Value::Any Talos::String::Literal::style(
    Runtime::Isolate *isolate, String::Dynamic message, Arguments &&arguments) {
    return style(isolate, message.view(), std::move(arguments));
}

Talos::Value::Any Talos::String::Literal::style(
    Runtime::Isolate *isolate, const $::String::View &message, Arguments &&arguments) {
    // clang-format off
    try { return Dynamic(isolate, fmt::vformat(message, std::move(arguments))); }
    catch (const std::exception &exception) { return report(isolate, exception); }
    // clang-format on
}

Talos::Value::Any Talos::String::Literal::report(Runtime::Isolate *isolate, const std::exception &exception) {
    return report(isolate, exception.what());
}

Talos::Value::Any Talos::String::Literal::report(Runtime::Isolate *isolate, const $::String::View &message) {
    return isolate->panic(6000403, $::Convert::capitalize(message));
}
