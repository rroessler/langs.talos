/// Talos Modules
#include "talos/member/storage.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_FIELDS(Monad::Result) {
    TALOS_XX_FIELDS_RESULT(X)
};
#undef X

//  PROPERTIES  //

#define X(N, ...) { #N, Field::N },
TALOS_BUILTIN_STORAGE(Monad::Result) = Talos::Member::Storage(name(), { TALOS_XX_FIELDS_RESULT(X) });
#undef X

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_FIELD(Monad::Result, is_okay, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Monad::Result, args.self());
    return Value::Boolean(args.self<Monad::Result>().success());
}

TALOS_MM_BUILTIN_FIELD(Monad::Result, is_error, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Monad::Result, args.self());
    return Value::Boolean(args.self<Monad::Result>().failure());
}

TALOS_MM_BUILTIN_FIELD(Monad::Result, unwrap_okay, isolate, args) {
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

TALOS_MM_BUILTIN_FIELD(Monad::Result, unwrap_error, isolate, args) {
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

Talos::Member::View TALOS_BUILTIN_TRAITS(Monad::Result)::m_attributes(const Monad::Result&, Value::Symbol symbol) {
    return m_members.retrieve(symbol);
}
