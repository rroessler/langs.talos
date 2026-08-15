/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) $_FWD(Talos::Builtins::Field, static Value::Any N(Isolate *, const Args &))
#include "talos/builtins/function/_defines/fields.def"

//  PROPERTIES  //

static auto s_members = Talos::Builtins::Storage<Talos::Function::Any>({
#define TALOS_XX_FIELDS_DEFINE(N, ...) {#N, Talos::Builtins::Field::N},
#include "talos/builtins/function/_defines/fields.def"
});

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Builtins::Field::arity(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, Function::Any, args.self());
  return Number::Tagged(args.self<Function::Any>().arity());
}

Talos::Value::Any Talos::Builtins::Field::adicity(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, Function::Any, args.self());
  return Number::Tagged(args.self<Function::Any>().adicity());
}

Talos::Value::Any Talos::Builtins::Field::receiver(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, Function::Any, args.self());
  return args.self<Function::Any>().receiver(); // get now
}

//  PRIVATE METHODS  //

Talos::Member::View
Talos::Builtins::Wrapper<Talos::Function::Any>::m_attribute(const Function::Any &, const Value::Symbol &symbol) {
  return s_members.retrieve(symbol);
}
