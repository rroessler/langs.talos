/// Talos Modules
#include "talos/string/literal.hpp"
#include "talos/function/args.hpp"
#include "talos/number/tagged.hpp"
#include "talos/runtime/isolate.hpp"

/// Forward Declarations
$_FWD(Talos::String::Literal, Value::Any report(Runtime::Isolate *, const std::exception &))
$_FWD(Talos::String::Literal, Value::Any report(Runtime::Isolate *, const $::String::View &))

//  PUBLIC METHODS  //

Talos::Value::Any
Talos::String::Literal::style(Runtime::Isolate *isolate, const String::Any &message, const Function::Args &args) {
  return style(isolate, message.view(), args);
}

Talos::Value::Any
Talos::String::Literal::style(Runtime::Isolate *isolate, const $::String::View &message, const Function::Args &args) {
  // prepare a string-stream for conversion
  auto oss = std::stringstream();

  // and construct the args to be used
  auto store = Args();
  store.reserve(args.size(), 0);

  // emplace each of the store values now
  for (const auto &value : args.span()) {
    if (value.is<Number::Tagged>()) store.push_back(value.as<Number::Tagged>().value());
    else oss << value, store.push_back(oss.str()), std::stringstream().swap(oss);
  }

  // and finally request styling now
  return style(isolate, message, std::move(store));
}

Talos::Value::Any Talos::String::Literal::style(Runtime::Isolate *isolate, const String::Any &message, Args &&args) {
  return style(isolate, message.view(), std::move(args));
}

Talos::Value::Any
Talos::String::Literal::style(Runtime::Isolate *isolate, const $::String::View &message, Args &&args) {
  // clang-format off
  try { return Any(isolate, fmt::vformat(message, std::move(args))); }
  catch (const std::exception &exception) { return report(isolate, exception); }
  // clang-format on
}

Talos::Value::Any Talos::String::Literal::report(Runtime::Isolate *isolate, const std::exception &exception) {
  return report(isolate, exception.what());
}

Talos::Value::Any Talos::String::Literal::report(Runtime::Isolate *isolate, const $::String::View &message) {
  return isolate->panic(6000403, $::Convert::capitalize(message));
}
