/// Forge Modules
#include "forge/member/factory.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/assert.ipp"

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct FORGE_BUILTIN_STATICS(String::Dynamic) {
    FORGE_XX_STATICS_STRING(X)
};
#undef X

//  PUBLIC METHODS  //

FORGE_MM_BUILTIN_STATIC(String::Dynamic, from, isolate, args) {
    FORGE_MM_ASSERT_ARGC(isolate, args.size(), 1);
    if (args[0].is<String::Dynamic>()) return args[0];
    auto buffer = $::Convert::stringify(args[0]);
    return String::Dynamic(isolate, buffer);
}

FORGE_MM_BUILTIN_STATIC(String::Dynamic, codepoint, isolate, args) {
    // ensure that our incoming details are validated
    FORGE_MM_ASSERT_ARGC(isolate, args.size(), 1);
    FORGE_MM_ASSERT_TYPEOF(isolate, Number::Tagged, args[0]);

    auto numeric = args.at<Number::Tagged>(0);  // get cp
    FORGE_MM_ASSERT_INTEGRAL(isolate, numeric.value());

    // should be able to safely attempt to cast outwards now
    auto codepoint = static_cast<int64_t>(numeric);
    FORGE_MM_ASSERT_BOUNDS(isolate, codepoint, 0, UINT32_MAX);
    return String::Small(static_cast<uint32_t>(codepoint));
}

//  PRIVATE METHODS  //

Forge::Value::Any FORGE_BUILTIN_TRAITS(String::Dynamic)::m_globals(Runtime::Isolate* isolate) {
    // construct the base object instance
    auto self = isolate->create<Object::Class>(name(), shape());

// assign the necessary fields now
#define X(N, ...) self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
    FORGE_XX_STATICS_STRING(X)
#undef X

    // and return the resulting instance
    return self;
}
