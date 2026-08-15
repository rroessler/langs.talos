/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define TALOS_XX_STATICS_DEFINE(N, ...) $_FWD(Talos::Builtins::Static, static Value::Any N(Isolate *, const Args &))
#include "talos/builtins/symbol/_defines/statics.def"

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Builtins::Static::from(Isolate *isolate, const Args &args) {
  // ensure the correct number of arguments given
  TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);

  // get the value to question and validate as needed
  auto value = args.at(0);

  // cast depending on the type of the value
  if (value.is<String::Any>()) return value.as<String::Any>().symbol();

  /// TODO: define a better hasher for other values
  return Value::Symbol();
}

//  PRIVATE METHODS  //

Talos::Value::Any
Talos::Builtins::Wrapper<Talos::Value::Symbol>::m_globals(Isolate *isolate, const Object::Class &self) {
#define TALOS_XX_STATICS_DEFINE(N, ...)                                                \
  self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
#include "talos/builtins/symbol/_defines/statics.def"

  // and return the resulting instance
  return self;
}
