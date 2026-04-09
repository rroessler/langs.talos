/// Talos Modules
#include "talos/member/factory.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"
#include "talos/builtins/_inline/defines.ipp"

//  TYPEDEFS  //

#define TALOS_XX_STATICS_DEFINE(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_STATICS(Number::Tagged) {
#include "talos/builtins/number/_defines/statics.def"
};
#undef TALOS_XX_STATICS_DEFINE

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_STATIC(Number::Tagged, parse, isolate, args) {
    // ensure the total incoming arguments now
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args[0]);

    // pull out the necessary properties now
    auto input = args.at<String::Dynamic>(0);
    auto radix = args.at(1, Value::Void());

    // attempt via a variety of options
    try {
        // if we have no-radix given (eg: undefined base), then revert to float
        if (radix.is<Value::Void>()) return Number::Tagged(std::stod(input.data()));

        // otherwise ensure we have a valid radix incoming
        TALOS_MM_ASSERT_TYPEOF(isolate, Number::Tagged, radix);

        // pull out the radix value to be used (eg: as a base)
        Number::Underlying base = radix.as<Number::Tagged>();

        // and attempt conversion now using integral parsing
        return Number::Tagged(std::stoll(input.data(), nullptr, base));
    } catch (...) {
        // otherwise default exceptions to be "NAN"
        return Number::Invalid();
    }
}

//  PRIVATE METHODS  //

Talos::Value::Any TALOS_BUILTIN_TRAITS(Number::Tagged)::m_globals(Runtime::Isolate* isolate) {
    // construct the base object instance
    auto self = isolate->create<Object::Class>(name(), shape());

// assign the necessary fields now
#define TALOS_XX_STATICS_DEFINE(N, ...) \
    self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
#include "talos/builtins/number/_defines/statics.def"
#undef TALOS_XX_STATICS_DEFINE

    // and return the resulting instance
    return self;
}
