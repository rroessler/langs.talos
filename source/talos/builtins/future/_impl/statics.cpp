/// Talos Includes
#include "talos/globals/service.hpp"

/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define TALOS_XX_STATICS_DEFINE(N, ...) $_FWD(Talos::Builtins::Static, static Value::Any N(Isolate *, const Args &))
#include "talos/builtins/future/_defines/statics.def"

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Builtins::Static::async(Isolate *isolate, const Args &args) {
  // validate the incoming passthrough arguments now
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  TALOS_MM_ASSERT_TYPEOF(isolate, Function::Any, args[0]);

  auto callback = args.at<Function::Any>(0); // prepare items now
  auto passthrough = Args(callback.receiver(), args.slice(1));

  // and attempt calling the future now
  return isolate->create<Async::Future>(callback, passthrough);
}

Talos::Value::Any Talos::Builtins::Static::delay(Isolate *isolate, const Args &args) {
  // validate the callback argument if given
  switch (args.size()) {
  default: TALOS_MM_ASSERT_TYPEOF(isolate, Function::Any, args[1]); $_FALLTHROUGH;
  case 1: TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args[0]); $_FALLTHROUGH;
  case 0: break; // can safely ignore when we are given no values here
  }

  // construct a callback for the delay handler
  static constexpr auto s_callback = [](Isolate *isolate, const Args &args) {
    auto milliseconds = args.at<Number::Tagged>(0, Number::Tagged(0));
    isolate->thread()->sleep($::Chrono::Milliseconds(milliseconds.value()));
    return args.size() > 1 ? isolate->invoke(args.at(1)) : Value::Void();
  };

  // construct the cached native to be used now
  auto *globals = isolate->service<Globals::Service>();
  static constexpr auto s_method = "Future.delay:callback";
  auto native = globals->internal(isolate, s_method, s_callback);

  // and construct the incoming future instance now
  return isolate->create<Async::Future>(native, args);
}

Talos::Value::Any Talos::Builtins::Static::resolve(Isolate *isolate, const Args &args) {
  auto value = args.at(0, Value::Void());
  auto future = isolate->create<Async::Future>();
  return future.thenable()->resolve(isolate, value), future;
}

Talos::Value::Any Talos::Builtins::Static::reject(Isolate *isolate, const Args &args) {
  auto reason = args.at(0, Value::Void());
  auto future = isolate->create<Async::Future>();
  return future.thenable()->reject(isolate, reason), future;
}

//  PRIVATE METHODS  //

Talos::Value::Any
Talos::Builtins::Wrapper<Talos::Async::Future>::m_globals(Isolate *isolate, const Object::Class &self) {
#define TALOS_XX_STATICS_DEFINE(N, ...)                                                \
  self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
#include "talos/builtins/future/_defines/statics.def"

  // and return the resulting instance
  return self;
}
