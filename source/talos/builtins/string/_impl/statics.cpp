/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define TALOS_XX_STATICS_DEFINE(N, ...) $_FWD(Talos::Builtins::Static, static Value::Any N(Isolate *, const Args &))
#include "talos/builtins/string/_defines/statics.def"

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Builtins::Static::from(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  if (args[0].is<String::Any>()) return args[0];
  return String::Literal::style(isolate, args[0]);
}

Talos::Value::Any Talos::Builtins::Static::codepoint(Isolate *isolate, const Args &args) {
  // ensure that our incoming details are validated
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
  TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args[0]);

  // get the numeric value for our incoming codepoint (ensuring integral)
  auto numeric = args.at<Number::Tagged>(0);
  TALOS_MM_ASSERT_INTEGRAL(isolate, numeric.value());

  // should be able to safely attempt to cast outwards now
  auto codepoint = static_cast<int64_t>(numeric);
  TALOS_MM_ASSERT_BOUNDS(isolate, codepoint, 0, UINT32_MAX);
  return String::Small(static_cast<uint32_t>(codepoint));
}

//  PRIVATE METHODS  //

Talos::Value::Any Talos::Builtins::Wrapper<Talos::String::Any>::m_globals(Isolate *isolate, const Object::Class &self) {
#define TALOS_XX_STATICS_DEFINE(N, ...)                                                \
  self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
#include "talos/builtins/string/_defines/statics.def"

  // and return the resulting instance
  return self;
}
