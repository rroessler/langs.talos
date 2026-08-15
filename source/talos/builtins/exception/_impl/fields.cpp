/// Builtin Includes
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) $_FWD(Talos::Builtins::Field, static Value::Any N(Isolate *, const Args &))
#include "talos/builtins/exception/_defines/fields.def"

//  PROPERTIES  //

static auto s_members = Talos::Builtins::Storage<Talos::Object::Exception>({
#define TALOS_XX_FIELDS_DEFINE(N, ...) {#N, Talos::Builtins::Field::N},
#include "talos/builtins/exception/_defines/fields.def"
});

//  PUBLIC METHODS  //

Talos::Value::Any Talos::Builtins::Field::name(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, Object::Exception, args.self());
  return args.self<Object::Exception>().name(); // get the name
}

Talos::Value::Any Talos::Builtins::Field::message(Isolate *isolate, const Args &args) {
  TALOS_MM_ASSERT_TYPEOF(isolate, Object::Exception, args.self());
  return args.self<Object::Exception>().message(); // get the name
}

//  PRIVATE METHODS  //

Talos::Member::View Talos::Builtins::Wrapper<Talos::Object::Exception>::m_attribute(
    const Object::Exception &, const Value::Symbol &symbol
) {
  return s_members.retrieve(symbol);
}
