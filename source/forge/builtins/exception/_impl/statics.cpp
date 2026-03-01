/// Forge Modules
#include "forge/member/factory.hpp"
#include "forge/string/literal.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct FORGE_BUILTIN_STATICS(Object::Exception) {
    FORGE_XX_STATICS_EXCEPTION(X)
};
#undef X

//  PUBLIC METHODS  //

FORGE_MM_BUILTIN_STATIC(Object::Exception, from, isolate, args) {
    // stop early if given no arguments at all
    if (args.empty()) return isolate->create<Object::Exception>();

    // ensure some conditions about the incoming details
    FORGE_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args[0]);

    // pull out some details from the arguments
    auto message = args.at<String::Dynamic>(0);

    // attempt formatting the exception now
    auto result = String::Literal::style(isolate, message, args.slice(1));

    // check if the incoming message is okay, if not then stop early
    if (!result.traits().okay() || !result.is<String::Dynamic>()) return result;

    // and resolve the exception to be constructed
    return isolate->create<Object::Exception>(result.as<String::Dynamic>());
}

FORGE_MM_BUILTIN_STATIC(Object::Exception, named, isolate, args) {
    // ensure some conditions about the incoming details
    FORGE_MM_ASSERT_ARGC(isolate, args.size(), 1);
    FORGE_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args[0]);
    if (args.size() > 1) FORGE_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args[1]);

    // pull out some details from the arguments
    auto name = args.at<String::Dynamic>(0);

    // attempt getting a suitable message now
    if (args.size() == 1) return isolate->create<Object::Exception>(name, String::Dynamic());

    // ensure we validate the incoming message value now
    FORGE_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args[1]);

    // update the incoming message now
    auto message = args.at<String::Dynamic>(1);

    // attempt formatting the exception now
    auto result = String::Literal::style(isolate, message, args.slice(2));

    // check if the incoming message is okay, if not then stop early
    if (!result.traits().okay() || !result.is<String::Dynamic>()) return result;

    // and resolve the exception to be constructed
    return isolate->create<Object::Exception>(name, result.as<String::Dynamic>());
}

//  PRIVATE METHODS  //

Forge::Value::Any FORGE_BUILTIN_TRAITS(Object::Exception)::m_globals(Runtime::Isolate* isolate) {
    // construct the base object instance
    auto self = isolate->create<Object::Class>(name(), shape());

// assign the necessary fields now
#define X(N, ...) self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
    FORGE_XX_STATICS_EXCEPTION(X)
#undef X

    // and return the resulting instance
    return self;
}
