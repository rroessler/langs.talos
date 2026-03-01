/// Forge Modules
#include "forge/member/factory.hpp"
#include "forge/string/literal.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct FORGE_BUILTIN_STATICS(Monad::Result) {
    FORGE_XX_STATICS_RESULT(X)
};
#undef X

//  PUBLIC METHODS  //

FORGE_MM_BUILTIN_STATIC(Monad::Result, wrap, isolate, args) {
    // validate the incoming results now
    FORGE_MM_ASSERT_ARGC(isolate, args.size(), 1);
    FORGE_MM_ASSERT_TYPEOF(isolate, Async::Future, args[0]);

    // prepare an accumulative result value
    Async::Result result = std::unexpected(Value::Failure());

    // attempt resolve a result whilst possible
    for (auto future = args[0]; future.is<Async::Future>();) {
        result = future.as<Async::Future>().await(isolate->thread());
        if (!result.has_value()) break;  // break on invalid results
    }

    // if the result return validly, then wrap
    if (result) return Monad::Success(isolate, *result);
    else return Monad::Failure(isolate, result.error());
}

FORGE_MM_BUILTIN_STATIC(Monad::Result, okay, isolate, args) {
    FORGE_MM_ASSERT_ARGC(isolate, args.size(), 1);
    return Monad::Success(isolate, args[0]);
}

FORGE_MM_BUILTIN_STATIC(Monad::Result, error, isolate, args) {
    FORGE_MM_ASSERT_ARGC(isolate, args.size(), 1);
    return Monad::Failure(isolate, args[0]);
}

//  PRIVATE METHODS  //

Forge::Value::Any FORGE_BUILTIN_TRAITS(Monad::Result)::m_globals(Runtime::Isolate* isolate) {
    // construct the base object instance
    auto self = isolate->create<Object::Class>(name(), shape());

// assign the necessary fields now
#define X(N, ...) self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
    FORGE_XX_STATICS_RESULT(X)
#undef X

    // and return the resulting instance
    return self;
}
