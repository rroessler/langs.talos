/// Talos Includes
#include "talos/globals/service.hpp"

/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

/// Forward Declarations
$_FWD(Talos::Builtins::Static, static Value::Any yield(Isolate *, const Args &))

//  TYPEDEFS  //

#define TALOS_XX_STATICS_DEFINE(N, ...) $_FWD(Talos::Builtins::Static, static Value::Any N(Isolate *, const Args &))
#include "talos/builtins/iterator/_defines/statics.def"

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Builtins::Static::yield(Isolate *isolate, const Args &args) {
  // ensure some valid conditions firstly
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  TALOS_MM_ASSERT_TYPEOF(isolate, Object::Instance, args.self());

  auto self = args.self(); // get details
  auto *descriptor = self.attribute("value");
  $_ASSERT(descriptor != nullptr); // check

  // attempt updating the incoming value now
  return descriptor->setter(isolate, self, args[0]);
}

Talos::Value::Any Talos::Builtins::Static::empty(Isolate *isolate, const Args &) {
  return isolate->create<Iterable::Iterator>();
}

Talos::Value::Any Talos::Builtins::Static::from(Isolate *isolate, const Args &args) {
  // ensure we have been given a suitable set of arguments
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);

  auto *descriptor = args[0].attribute(Operator::Kind::ITER); // pull out the iterable
  if (descriptor == nullptr) descriptor = args[0].attribute(Operator::Attribute::ITER);
  auto attribute = descriptor ? descriptor->getter(isolate, args[0]) : Value::Missing();
  return attribute.pointer().okay() ? attribute : isolate->panic(6000502, args[0].brand());
}

Talos::Value::Any Talos::Builtins::Static::dynamic(Isolate *isolate, const Args &args) {
  // ensure we have been given a suitable set of arguments
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  TALOS_MM_ASSERT_TYPEOF(isolate, Function::Any, args[0]);

  // pull out the incoming function now
  auto generator = args.at<Function::Any>(0);

  // create at context to be used for our iterator callback (helps bind all GC references together)
  auto context = isolate->create<Object::Instance>();

  // prepare the incoming yield handler so it is cached only once
  auto *globals = isolate->service<Globals::Service>();
  static constexpr auto s_method = "Iterator.dynamic:yield";
  auto yield = globals->internal(isolate, s_method, Static::yield);

  // we bind the context with the necessary properties for iteration
  context.fields().emplace("next", Member::Factory::reference(generator));
  context.fields().emplace("value", Member::Factory::reference(Value::Void()));
  context.fields().emplace("yield", Member::Factory::reference(isolate->bind(yield, context)));

  // prepare the callback to be used for the iterator
  Iterable::Callback<Object::Instance> callback = [](auto *isolate, Object::Instance self, size_t idx) -> Value::Any {
    // prepare the available properties contained
    auto next = self.attribute("next")->getter(isolate, self);
    auto yield = self.attribute("yield")->getter(isolate, self);

    // prepare the arguments to be used now
    std::vector<Value::Any> args = {Number::Tagged(idx), yield};

    // attempt getting the next handler now
    auto done = isolate->invoke(next, Function::Args(args));

    // check whether or not the operation has now ended
    if (!done.pointer().okay()) return Value::Failure();
    else if (done.truthiness()) return Value::Sentinel();
    else return self.attribute("value")->getter(isolate, self);
  };

  // and now we want to rebuild the iterator as necessary
  return isolate->create<Iterable::Iterator>(context, std::move(callback));
}

//  PRIVATE METHODS  //

Talos::Value::Any
Talos::Builtins::Wrapper<Talos::Iterable::Iterator>::m_globals(Isolate *isolate, const Object::Class &self) {
#define TALOS_XX_STATICS_DEFINE(N, ...)                                                \
  self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
#include "talos/builtins/iterator/_defines/statics.def"

  // and return the resulting instance
  return self;
}
