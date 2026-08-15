/// Talos Includes
#include "talos/member/factory.hpp"
#include "talos/runtime/isolate.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/builtins.ipp"

//  TYPEDEFS   //

#define TALOS_XX_FIELDS_DEFINE(N, ...) $_FWD(Talos::Builtins::Field, static Value::Any N(Isolate *, const Args &))
#include "talos/builtins/debug/_defines/fields.def"

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Builtins::Field::print(Isolate *, const Args &args) {
  return $::Debug::print("{0}", fmt::join(args.span(), " ")), Value::Void();
}

Talos::Value::Any Talos::Builtins::Field::eprint(Isolate *, const Args &args) {
  return $::Debug::eprint("{0}", fmt::join(args.span(), " ")), Value::Void();
}

Talos::Value::Any Talos::Builtins::Field::println(Isolate *, const Args &args) {
  return $::Debug::println("{0}", fmt::join(args.span(), " ")), Value::Void();
}

Talos::Value::Any Talos::Builtins::Field::eprintln(Isolate *, const Args &args) {
  return $::Debug::eprintln("{0}", fmt::join(args.span(), " ")), Value::Void();
}

Talos::Value::Any Talos::Builtins::Field::breakpoint(Isolate *isolate, const Args &) {
  return isolate->todo("Unimplemented 'Debug.breakpoint'");
}

//  PRIVATE METHODS  //

Talos::Value::Any Talos::Builtins::Wrapper<Talos::Builtins::Custom::Debug>::m_globals(Isolate *isolate) {
  // construct the base object instance
  auto self = isolate->create<Object::Instance>();

  // assign all the available fields to be used
#define TALOS_XX_FIELDS_DEFINE(N, ...)                                               \
  self.fields().emplace(#N, Member::Factory::native(isolate, Field::N, name(), #N));
#include "talos/builtins/debug/_defines/fields.def"

  // and return the resulting instance
  return self;
}
