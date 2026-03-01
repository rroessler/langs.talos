/// Forge Modules
#include "forge/member/factory.hpp"

/// Builtin Modules
#include "forge/builtins/_inline/assert.ipp"

//  MACROS  //

#define MM_VARIANT_RESOLVE(V, I, A, ...)                      \
    FORGE_MM_ASSERT_ARGC(I, A.size(), 2);                     \
    FORGE_MM_ASSERT_TYPEOF(I, Object::Enum, A[0]);            \
    FORGE_MM_ASSERT_TYPEOF(I, Number::Tagged, A[1]);          \
                                                              \
    auto enumeration = args.at<Object::Enum>(0);              \
    auto V = enumeration.resolve(args.at<Number::Tagged>(1)); \
    return V ? Value::Any(V->__VA_ARGS__) : I->panic("...");

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct FORGE_BUILTIN_STATICS(Object::Enum) {
    FORGE_XX_STATICS_ENUM(X)

    /// @brief Handles resolving incoming variants.
    static const Object::Variant* resolve(Runtime::Isolate*, const Function::Arguments&);
};
#undef X

//  PUBLIC METHODS  //

FORGE_MM_BUILTIN_STATIC(Object::Enum, name, isolate, args) { MM_VARIANT_RESOLVE(variant, isolate, args, name); }
FORGE_MM_BUILTIN_STATIC(Object::Enum, label, isolate, args) { MM_VARIANT_RESOLVE(variant, isolate, args, label); }
FORGE_MM_BUILTIN_STATIC(Object::Enum, value, isolate, args) {
    MM_VARIANT_RESOLVE(variant, isolate, args, value->reference());
}

//  PRIVATE METHODS  //

Forge::Value::Any FORGE_BUILTIN_TRAITS(Object::Enum)::m_globals(Runtime::Isolate* isolate) {
    // construct the base object instance
    auto self = isolate->create<Object::Class>(name(), shape());

// assign the necessary fields now
#define X(N, ...) self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
    FORGE_XX_STATICS_ENUM(X)
#undef X

    // and return the resulting instance
    return self;
}
