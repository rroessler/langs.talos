/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) $_FWD(Talos::Builtins::Field, static Value::Any N(Isolate *, const Args &))
#include "talos/builtins/iterator/_defines/fields.def"

//  PROPERTIES  //

static auto s_members = Talos::Builtins::Storage<Talos::Iterable::Iterator>({
#define TALOS_XX_FIELDS_DEFINE(N, ...) {#N, Talos::Builtins::Field::N},
#include "talos/builtins/iterator/_defines/fields.def"
});

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Builtins::Field::done(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::Iterator, args.self());
  return Value::Boolean(args.self<Iterable::Iterator>().done());
}

Talos::Value::Any Talos::Builtins::Field::next(Isolate *isolate, const Args &args) {
  // validate the incoming iterator now
  TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::Iterator, args.self());

  // pull out our necessary details
  auto iterator = args.self<Iterable::Iterator>();
  Value::Any result = Value::Boolean(iterator.next(isolate));

  // and validate the result now
  return iterator.okay() ? result : Value::Failure();
}

Talos::Value::Any Talos::Builtins::Field::index(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::Iterator, args.self());
  return Number::Tagged(args.self<Iterable::Iterator>().index());
}

//  PRIVATE METHODS  //

Talos::Member::View Talos::Builtins::Wrapper<Talos::Iterable::Iterator>::m_attribute(
    const Iterable::Iterator &, const Value::Symbol &symbol
) {
  return s_members.retrieve(symbol);
}
