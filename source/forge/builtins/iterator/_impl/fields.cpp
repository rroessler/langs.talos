/// Forge Modules
#include "forge/member/storage.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct FORGE_BUILTIN_FIELDS(Iterable::Iterator) {
    FORGE_XX_FIELDS_ITERATOR(X)
};
#undef X

//  PROPERTIES  //

#define X(N, ...) { #N, Field::N },
FORGE_BUILTIN_STORAGE(Iterable::Iterator) = Forge::Member::Storage(name(), { FORGE_XX_FIELDS_ITERATOR(X) });
#undef X

//  PUBLIC METHODS  //

FORGE_MM_BUILTIN_FIELD(Iterable::Iterator, done, isolate, args) {
    FORGE_MM_ASSERT_TYPEOF(isolate, Iterable::Iterator, args.self());
    return Value::Boolean(args.self<Iterable::Iterator>().done());
}

FORGE_MM_BUILTIN_FIELD(Iterable::Iterator, next, isolate, args) {
    // validate the incoming iterator now
    FORGE_MM_ASSERT_TYPEOF(isolate, Iterable::Iterator, args.self());

    // pull out our necessary details
    auto iterator = args.self<Iterable::Iterator>();
    Value::Any result = Value::Boolean(iterator.next(isolate));

    // and validate the result now
    return iterator.okay() ? result : Value::Failure();
}

FORGE_MM_BUILTIN_FIELD(Iterable::Iterator, index, isolate, args) {
    FORGE_MM_ASSERT_TYPEOF(isolate, Iterable::Iterator, args.self());
    return Number::Tagged(args.self<Iterable::Iterator>().index());
}

//  PRIVATE METHODS  //

Forge::Member::View FORGE_BUILTIN_TRAITS(Iterable::Iterator)::m_attributes(
    const Iterable::Iterator&, Value::Symbol symbol) {
    return m_members.retrieve(symbol);
}
