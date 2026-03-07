/// Talos Modules
#include "talos/globals/service.hpp"
#include "talos/member/storage.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_FIELDS(Async::Future) {
    TALOS_XX_FIELDS_FUTURE(X)
};
#undef X

//  PROPERTIES  //

#define X(N, ...) { #N, Field::N },
TALOS_BUILTIN_STORAGE(Async::Future) = Talos::Member::Storage(name(), { TALOS_XX_FIELDS_FUTURE(X) });
#undef X

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_FIELD(Async::Future, then, isolate, args) {
    // ensure some conditions about the arguments
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, Async::Future, args.self());
    TALOS_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args[0]);

    // prepare the baseline callback now
    static constexpr auto s_callback = [](Runtime::Isolate* isolate, const Function::Arguments& args) {
        // prepare the incoming items now
        auto self = args.self<Async::Future>();
        auto handler = args.at<Function::Dynamic>(0);

        // wait for the current future to finish
        auto result = self.await(isolate);

        // prepare the invocation elements now
        std::span<Value::Any> span = { &result, 1 };

        // and attempt mapping our incoming result now
        return result.traits().okay() ? isolate->invoke(handler, span) : result;
    };

    // construct the cached native to be used now
    auto native = TALOS_MM_GLOBALS_NATIVE(isolate, "Future.then:callback", s_callback);

    // and construct the incoming future instance now
    return isolate->create<Async::Future>(native, args);
}

TALOS_MM_BUILTIN_FIELD(Async::Future, fails, isolate, args) {
    // ensure some conditions about the arguments
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, Async::Future, args.self());
    TALOS_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args[0]);

    // attempt converting to another future
    static constexpr auto s_callback = [](Runtime::Isolate* isolate, const Function::Arguments& args) {
        // prepare the incoming items now
        auto self = args.self<Async::Future>();
        auto handler = args.at<Function::Dynamic>(0);

        // wait for the current future to finish
        auto result = self.await(isolate->thread());

        // if we have a normal result, then return
        if (result.has_value()) return *result;

        // otherwise attempt mapping now
        std::span<Value::Any> span = { &result.error(), 1 };
        return isolate->invoke(handler, span);  // valid here
    };

    // construct the cached native to be used now
    auto native = TALOS_MM_GLOBALS_NATIVE(isolate, "Future.fails:callback", s_callback);

    // and construct the incoming future instance now
    return isolate->create<Async::Future>(native, args);
}

TALOS_MM_BUILTIN_FIELD(Async::Future, await, isolate, args) {
    // prepare the initial result value
    auto result = args.self();

    // attempt iterating whilst possible to do so
    while (result.is<Async::Future>()) result = result.as<Async::Future>().await(isolate);

    // we now have a non-future result so return
    return result;
}

TALOS_MM_BUILTIN_FIELD(Async::Future, state, isolate, args) {
    TALOS_MM_ASSERT_TYPEOF(isolate, Async::Future, args.self());
    auto status = args.self<Async::Future>().status();
    return Number::Tagged(static_cast<uint8_t>(status));
}

//  PRIVATE METHODS  //

Talos::Member::View TALOS_BUILTIN_TRAITS(Async::Future)::m_attributes(const Async::Future&, Value::Symbol symbol) {
    return m_members.retrieve(symbol);
}
