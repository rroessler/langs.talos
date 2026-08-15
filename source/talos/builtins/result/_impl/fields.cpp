/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) $_FWD(Talos::Builtins::Field, static Value::Any N(Isolate *, const Args &))
#include "talos/builtins/result/_defines/fields.def"

//  PROPERTIES  //

static auto s_members = Talos::Builtins::Storage<Talos::Monad::Result>({
#define TALOS_XX_FIELDS_DEFINE(N, ...) {#N, Talos::Builtins::Field::N},
#include "talos/builtins/result/_defines/fields.def"
});

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Builtins::Field::is_okay(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, Monad::Result, args.self());
  return Value::Boolean(args.self<Monad::Result>().success());
}

Talos::Value::Any Talos::Builtins::Field::is_error(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, Monad::Result, args.self());
  return Value::Boolean(args.self<Monad::Result>().failure());
}

Talos::Value::Any Talos::Builtins::Field::unwrap_okay(Isolate *isolate, const Args &args) {
  // attempt parsing the incoming value
  TALOS_MM_ASSERT_TYPEOF(isolate, Monad::Result, args.self());

  // get the baseline result value
  auto result = args.self<Monad::Result>();

  // succeed immediately if the result is okay
  if (result.success()) return result.storage();

  // otherwise throw an error as needed
  if (args.empty()) return isolate->panic(6000701);
  else return isolate->panic(6000700, args[1]);
}

Talos::Value::Any Talos::Builtins::Field::unwrap_error(Isolate *isolate, const Args &args) {
  // attempt parsing the incoming value
  TALOS_MM_ASSERT_TYPEOF(isolate, Monad::Result, args.self());

  // get the baseline result value
  auto result = args.self<Monad::Result>();

  // succeed immediately if the result is an error
  if (result.failure()) return result.storage();

  // otherwise throw an error as needed
  if (args.empty()) return isolate->panic(6000702);
  else return isolate->panic(6000700, args[1]);
}

//  PRIVATE METHODS  //

Talos::Member::View
Talos::Builtins::Wrapper<Talos::Monad::Result>::m_attribute(const Monad::Result &, const Value::Symbol &symbol) {
  return s_members.retrieve(symbol);
}
