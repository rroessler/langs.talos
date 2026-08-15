/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define TALOS_XX_STATICS_DEFINE(N, ...) $_FWD(Talos::Builtins::Static, static Value::Any N(Isolate *, const Args &))
#include "talos/builtins/result/_defines/statics.def"

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Builtins::Static::wrap(Isolate *isolate, const Args &args) {
  // validate the incoming results now
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  TALOS_MM_ASSERT_TYPEOF(isolate, Async::Future, args[0]);

  // prepare an accumulative result value
  Async::Result result = std::unexpected(Value::Failure());

  // attempt resolve a result whilst possible
  for (auto future = args[0]; future.is<Async::Future>();) {
    result = future.as<Async::Future>().await(isolate->thread());
    if (!result.has_value()) break; // break on invalid results
  }

  // if the result return validly, then wrap
  if (result) return Monad::Success(isolate, *result);
  else return Monad::Failure(isolate, result.error());
}

Talos::Value::Any Talos::Builtins::Static::okay(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  return Monad::Success(isolate, args[0]);
}

Talos::Value::Any Talos::Builtins::Static::error(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  return Monad::Failure(isolate, args[0]);
}

//  PRIVATE METHODS  //

Talos::Value::Any
Talos::Builtins::Wrapper<Talos::Monad::Result>::m_globals(Isolate *isolate, const Object::Class &self) {
#define TALOS_XX_STATICS_DEFINE(N, ...)                                                \
  self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
#include "talos/builtins/result/_defines/statics.def"

  // and return the resulting instance
  return self;
}
