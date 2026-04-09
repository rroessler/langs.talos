/// Talos Modules
#include "talos/member/factory.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"
#include "talos/builtins/_inline/defines.ipp"

//  MACROS  //

#define MM_VARIANT_RESOLVE(V, I, A, ...)                      \
    TALOS_MM_ASSERT_ARGC(I, A.size(), 2);                     \
    TALOS_MM_ASSERT_TYPEOF(I, Object::Enum, A[0]);            \
    TALOS_MM_ASSERT_TYPEOF(I, Number::Tagged, A[1]);          \
                                                              \
    auto enumeration = args.at<Object::Enum>(0);              \
    auto V = enumeration.resolve(args.at<Number::Tagged>(1)); \
    return V ? Value::Any(V->__VA_ARGS__) : I->panic("...");

//  TYPEDEFS  //

#define TALOS_XX_STATICS_DEFINE(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_STATICS(Object::Enum) {
#include "talos/builtins/enum/_defines/statics.def"

    /// @brief Handles resolving incoming variants.
    static const Object::Variant* resolve(Runtime::Isolate*, const Function::Arguments&);
};
#undef TALOS_XX_STATICS_DEFINE

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_STATIC(Object::Enum, name, isolate, args) { MM_VARIANT_RESOLVE(variant, isolate, args, name); }
TALOS_MM_BUILTIN_STATIC(Object::Enum, label, isolate, args) { MM_VARIANT_RESOLVE(variant, isolate, args, label); }
TALOS_MM_BUILTIN_STATIC(Object::Enum, value, isolate, args) {
    MM_VARIANT_RESOLVE(variant, isolate, args, value->reference());
}

//  PRIVATE METHODS  //

Talos::Value::Any TALOS_BUILTIN_TRAITS(Object::Enum)::m_globals(Runtime::Isolate* isolate) {
    // construct the base object instance
    auto self = isolate->create<Object::Class>(name(), shape());

// assign the necessary fields now
#define TALOS_XX_STATICS_DEFINE(N, ...) \
    self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
#include "talos/builtins/enum/_defines/statics.def"
#undef TALOS_XX_STATICS_DEFINE

    // and return the resulting instance
    return self;
}
