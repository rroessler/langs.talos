/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

/// Forward Declarations
$_FWD(Talos::Builtins::Detail, using Callback = Value::Any (*)(const Object::Variant *))
$_FWD(Talos::Builtins::Static, static Value::Any resolve(Isolate *isolate, const Args &args, Detail::Callback callback))

//  TYPEDEFS  //

#define TALOS_XX_STATICS_DEFINE(N, ...) $_FWD(Talos::Builtins::Static, static Value::Any N(Isolate *, const Args &))
#include "talos/builtins/enum/_defines/statics.def"

//  PUBLIC METHODS  //

static Talos::Value::Any
Talos::Builtins::Static::resolve(Isolate *isolate, const Args &args, Detail::Callback callback) {
  // validate some details about the incoming items
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 2);
  TALOS_MM_ASSERT_TYPEOF(isolate, Object::Enum, args[0]);
  TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args[1]);

  // pull out the value in question to be resolved
  auto ordinal = args.at<Number::Tagged>(1);
  auto enumeration = args.at<Object::Enum>(0);
  auto variant = enumeration.resolve(ordinal);
  return variant ? callback(variant) : isolate->panic(4000500, ordinal);
}

Talos::Value::Any Talos::Builtins::Static::name(Isolate *isolate, const Args &args) {
  return resolve(isolate, args, [](const Object::Variant *variant) -> Value::Any { return variant->name; });
}

Talos::Value::Any Talos::Builtins::Static::label(Isolate *isolate, const Args &args) {
  return resolve(isolate, args, [](const Object::Variant *variant) -> Value::Any { return variant->label; });
}

Talos::Value::Any Talos::Builtins::Static::value(Isolate *isolate, const Args &args) {
  return resolve(isolate, args, [](const Object::Variant *variant) { return variant->value->reference(); });
}

//  PRIVATE METHODS  //

Talos::Value::Any
Talos::Builtins::Wrapper<Talos::Object::Enum>::m_globals(Isolate *isolate, const Object::Class &self) {
#define TALOS_XX_STATICS_DEFINE(N, ...)                                                \
  self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
#include "talos/builtins/enum/_defines/statics.def"

  // and return the resulting instance
  return self;
}
