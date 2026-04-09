/// Talos Modules
#include "talos/member/storage.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"
#include "talos/builtins/_inline/defines.ipp"

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_FIELDS(Iterable::Iterator) {
#include "talos/builtins/iterator/_defines/fields.def"
};
#undef TALOS_XX_FIELDS_DEFINE

//  PROPERTIES  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) { #N, Field::N },
TALOS_BUILTIN_STORAGE(Iterable::Iterator) = Talos::Member::Storage(name(), {
#include "talos/builtins/iterator/_defines/fields.def"
                                                                           });
#undef TALOS_XX_FIELDS_DEFINE

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_FIELD(Iterable::Iterator, done, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::Iterator, args.self());
    return Value::Boolean(args.self<Iterable::Iterator>().done());
}

TALOS_MM_BUILTIN_FIELD(Iterable::Iterator, next, isolate, args) {
    // validate the incoming iterator now
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::Iterator, args.self());

    // pull out our necessary details
    auto iterator = args.self<Iterable::Iterator>();
    Value::Any result = Value::Boolean(iterator.next(isolate));

    // and validate the result now
    return iterator.okay() ? result : Value::Failure();
}

TALOS_MM_BUILTIN_FIELD(Iterable::Iterator, index, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::Iterator, args.self());
    return Number::Tagged(args.self<Iterable::Iterator>().index());
}

//  PRIVATE METHODS  //

Talos::Member::View TALOS_BUILTIN_TRAITS(Iterable::Iterator)::m_attributes(
    const Iterable::Iterator&, Value::Symbol symbol) {
    return m_members.retrieve(symbol);
}
