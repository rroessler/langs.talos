/// Talos Modules
#include "talos/member/factory.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"
#include "talos/builtins/_inline/defines.ipp"

//  TYPEDEFS  //

#define TALOS_XX_STATICS_DEFINE(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_STATICS(Function::Dynamic) {
#include "talos/builtins/function/_defines/statics.def"
};
#undef TALOS_XX_STATICS_DEFINE

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_STATIC(Function::Dynamic, vlimit, , ) { return Number::Tagged(UINT64_MAX); }

TALOS_MM_BUILTIN_STATIC(Function::Dynamic, call, isolate, args) {
    // ensure we have some valid values as necessary now
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args[0]);

    // prepare the dynamic arguments now
    auto functor = args.at<Function::Dynamic>(0);

    // attempt calling the instance now
    return isolate->invoke(functor, args.slice(1));
}

TALOS_MM_BUILTIN_STATIC(Function::Dynamic, apply, isolate, args) {
    // ensure we have some valid values as necessary now
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, Function::Dynamic, args[0]);

    // prepare the dynamic arguments and callable
    auto functor = args.at<Function::Dynamic>(0);

    // this means we have a baseline callable value
    if (args.size() == 1) return isolate->invoke(functor);

    // ensure we now have an iterable list now
    TALOS_MM_ASSERT_TYPEOF(isolate, Iterable::List, args[1]);
    return isolate->invoke(functor, args.at<Iterable::List>(1).span());
}

//  PRIVATE METHODS  //

Talos::Value::Any TALOS_BUILTIN_TRAITS(Function::Dynamic)::m_globals(Runtime::Isolate* isolate) {
    // construct the base object instance
    auto self = isolate->create<Object::Class>(name(), shape());

// assign the necessary fields now
#define TALOS_XX_STATICS_DEFINE(N, ...) \
    self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
#include "talos/builtins/function/_defines/statics.def"
#undef TALOS_XX_STATICS_DEFINE

    // and return the resulting instance
    return self;
}
