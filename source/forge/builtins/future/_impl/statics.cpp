/// Forge Modules
#include "forge/async/service.hpp"
#include "forge/engine/dispatch.hpp"
#include "forge/globals/service.hpp"
#include "forge/member/factory.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct FORGE_BUILTIN_STATICS(Async::Future) {
    FORGE_XX_STATICS_FUTURE(X)
};
#undef X

//  PUBLIC METHODS  //

FORGE_MM_BUILTIN_STATIC(Async::Future, async, isolate, args) {
    // validate the incoming passthrough arguments now
    FORGE_MM_ASSERT_ARGC(isolate, args.size(), 1);
    FORGE_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args[0]);

    auto callback = args.at<Function::Dynamic>(0);  // prepare items now
    auto passthrough = Function::Arguments(callback.receiver(), args.slice(1));

    // and attempt calling the future now
    return isolate->create<Async::Future>(callback, passthrough);
}

FORGE_MM_BUILTIN_STATIC(Async::Future, delay, isolate, args) {
    // validate the incoming passthrough arguments now
    FORGE_MM_ASSERT_ARGC(isolate, args.size(), 1);
    FORGE_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args[0]);

    // validate the callback argument if given
    if (args.size() > 1) FORGE_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args[1]);

    // construct a callback for the delay handler
    static constexpr auto s_callback = [](Runtime::Isolate* isolate, const Function::Arguments& args) {
        $::Chrono::Milliseconds duration = args.at<Number::Tagged>(0).value();
        isolate->thread()->sleep(duration);  // sleep now for as needed
        return args.size() > 1 ? isolate->invoke(args.at(1)) : Value::Void();
    };

    // construct the cached native to be used now
    auto native = FORGE_MM_GLOBALS_NATIVE(isolate, "Future.delay:callback", s_callback);

    // and construct the incoming future instance now
    return isolate->create<Async::Future>(native, args);
}

FORGE_MM_BUILTIN_STATIC(Async::Future, resolve, isolate, args) {
    auto value = args.at(0, Value::Void());
    auto future = isolate->create<Async::Future>();
    return future.thenable()->resolve(isolate, value), future;
}

FORGE_MM_BUILTIN_STATIC(Async::Future, reject, isolate, args) {
    auto reason = args.at(0, Value::Void());
    auto future = isolate->create<Async::Future>();
    return future.thenable()->reject(isolate, reason), future;
}

//  PRIVATE METHODS  //

Forge::Value::Any FORGE_BUILTIN_TRAITS(Async::Future)::m_globals(Runtime::Isolate* isolate) {
    // construct the base object instance
    auto self = isolate->create<Object::Class>(name(), shape());

// assign the necessary fields now
#define X(N, ...) self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
    FORGE_XX_STATICS_FUTURE(X)
#undef X

    // and return the resulting instance
    return self;
}
