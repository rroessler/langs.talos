/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) $_FWD(Talos::Builtins::Field, static Value::Any N(Isolate *, const Args &))
#include "talos/builtins/symbol/_defines/fields.def"

//  PROPERTIES  //

static auto s_members = Talos::Builtins::Storage<Talos::Value::Symbol>({
#define TALOS_XX_FIELDS_DEFINE(N, ...) {#N, Talos::Builtins::Field::N},
#include "talos/builtins/symbol/_defines/fields.def"
});

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Builtins::Field::hash(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, Value::Symbol, args.self());
  return Number::Tagged(args.self<Value::Symbol>().hash());
}

//  PRIVATE METHODS  //

Talos::Member::View
Talos::Builtins::Wrapper<Talos::Value::Symbol>::m_attribute(const Value::Symbol &, const Value::Symbol &symbol) {
  return s_members.retrieve(symbol);
}
