/// Talos Modules
#include "talos/member/factory.hpp"
#include "talos/string/literal.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"
#include "talos/builtins/_inline/defines.ipp"

//  TYPEDEFS  //

#define TALOS_XX_STATICS_DEFINE(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_STATICS(Monad::Result) {
#include "talos/builtins/result/_defines/statics.def"
};
#undef TALOS_XX_STATICS_DEFINE

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_STATIC(Monad::Result, wrap, isolate, args) {
    // validate the incoming results now
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, Async::Future, args[0]);

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

TALOS_MM_BUILTIN_STATIC(Monad::Result, okay, isolate, args) {
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    return Monad::Success(isolate, args[0]);
}

TALOS_MM_BUILTIN_STATIC(Monad::Result, error, isolate, args) {
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    return Monad::Failure(isolate, args[0]);
}

//  PRIVATE METHODS  //

Talos::Value::Any TALOS_BUILTIN_TRAITS(Monad::Result)::m_globals(Runtime::Isolate* isolate) {
    // construct the base object instance
    auto self = isolate->create<Object::Class>(name(), shape());

// assign the necessary fields now
#define TALOS_XX_STATICS_DEFINE(N, ...) \
    self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
#include "talos/builtins/result/_defines/statics.def"
#undef TALOS_XX_STATICS_DEFINE

    // and return the resulting instance
    return self;
}
