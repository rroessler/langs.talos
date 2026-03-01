/// Forge Modules
#include "forge/member/storage.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct FORGE_BUILTIN_FIELDS(Monad::Result) {
    FORGE_XX_FIELDS_RESULT(X)
};
#undef X

//  PROPERTIES  //

#define X(N, ...) { #N, Field::N },
FORGE_BUILTIN_STORAGE(Monad::Result) = Forge::Member::Storage(name(), { FORGE_XX_FIELDS_RESULT(X) });
#undef X

//  PUBLIC METHODS  //

FORGE_MM_BUILTIN_FIELD(Monad::Result, is_okay, isolate, args) {
    FORGE_MM_ASSERT_TYPEOF(isolate, Monad::Result, args.self());
    return Value::Boolean(args.self<Monad::Result>().success());
}

FORGE_MM_BUILTIN_FIELD(Monad::Result, is_error, isolate, args) {
    FORGE_MM_ASSERT_TYPEOF(isolate, Monad::Result, args.self());
    return Value::Boolean(args.self<Monad::Result>().failure());
}

FORGE_MM_BUILTIN_FIELD(Monad::Result, unwrap_okay, isolate, args) {
    // attempt parsing the incoming value
    FORGE_MM_ASSERT_TYPEOF(isolate, Monad::Result, args.self());

    // get the baseline result value
    auto result = args.self<Monad::Result>();

    // succeed immediately if the result is okay
    if (result.success()) return result.storage();

    // otherwise throw an error as needed
    if (args.empty()) return isolate->panic(6000701);
    else return isolate->panic(6000700, args[1]);
}

FORGE_MM_BUILTIN_FIELD(Monad::Result, unwrap_error, isolate, args) {
    // attempt parsing the incoming value
    FORGE_MM_ASSERT_TYPEOF(isolate, Monad::Result, args.self());

    // get the baseline result value
    auto result = args.self<Monad::Result>();

    // succeed immediately if the result is an error
    if (result.failure()) return result.storage();

    // otherwise throw an error as needed
    if (args.empty()) return isolate->panic(6000702);
    else return isolate->panic(6000700, args[1]);
}

//  PRIVATE METHODS  //

Forge::Member::View FORGE_BUILTIN_TRAITS(Monad::Result)::m_attributes(const Monad::Result&, Value::Symbol symbol) {
    return m_members.retrieve(symbol);
}
