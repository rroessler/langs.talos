/// Talos Modules
#include "talos/member/factory.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/assert.ipp"
#include "talos/builtins/_inline/defines.ipp"

//  TYPEDEFS  //

#define TALOS_XX_STATICS_DEFINE(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_STATICS(Value::Boolean) {
#include "talos/builtins/boolean/_defines/statics.def"
};
#undef TALOS_XX_STATICS_DEFINE

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_STATIC(Value::Boolean, from, isolate, args) {
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);
    return Value::Boolean(args.at(0).truthiness());
}

TALOS_MM_BUILTIN_STATIC(Value::Boolean, parse, isolate, args) {
    TALOS_MM_ASSERT_ARGC(isolate, args.size(), 1);  // prepare
    TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, args[0]);

    // attempt resolving a suitable source and case-sensitivity
    auto input = args.at<String::Dynamic>(0);
    auto sensitive = args.at(1, Value::Boolean(false)).truthiness();

    // the source requires a backing from the base input string
    auto source = input.view();

// define a specialized macro for exiting
#define MM_PARSE_FAILURE \
    if (sensitive) goto _PARSE_FAILURE

// define a specialized macros for fast-delegation
#define MM_PARSE_CLOSE(...) }
#define MM_PARSE_OPEN(N, L, U, ...) \
    switch (source[N]) {            \
        case L: MM_PARSE_FAILURE;   \
        case U: __VA_ARGS__

#define XX_TRUE_CHAIN(X) \
    X(1, 'r', 'R')       \
    X(2, 'u', 'U')       \
    X(3, 'e', 'E')

#define XX_FALSE_CHAIN(X) \
    X(1, 'a', 'A')        \
    X(2, 'l', 'L')        \
    X(3, 's', 'S')        \
    X(4, 'e', 'E')

    // stop early if the sizing is invalid
    if (source.size() < 4 || source.size() > 5) goto _PARSE_FAILURE;

    // attempt handling with exactness now
    switch (source[0]) {
        case 't': MM_PARSE_FAILURE;
        case 'T':
            XX_TRUE_CHAIN(MM_PARSE_OPEN)
            return Value::Boolean(true);
            XX_TRUE_CHAIN(MM_PARSE_CLOSE);

        case 'f': MM_PARSE_FAILURE;
        case 'F':
            XX_FALSE_CHAIN(MM_PARSE_OPEN)
            return Value::Boolean(false);
            XX_FALSE_CHAIN(MM_PARSE_CLOSE);

        // otherwise break for failures
        default: break;
    }

#undef XX_TRUE_CHAIN
#undef XX_FALSE_CHAIN

#undef MM_PARSE_OPEN
#undef MM_PARSE_CLOSE
#undef MM_PARSE_FAILURE

_PARSE_FAILURE:
    return isolate->panic(6000404, name(), source);
}

//  PRIVATE METHODS  //

Talos::Value::Any TALOS_BUILTIN_TRAITS(Value::Boolean)::m_globals(Runtime::Isolate* isolate) {
    // construct the base object instance
    auto self = isolate->create<Object::Class>(name(), shape());

// assign the necessary fields now
#define TALOS_XX_STATICS_DEFINE(N, ...) \
    self.statics().emplace(#N, Member::Factory::native(isolate, Static::N, name(), #N));
#include "talos/builtins/boolean/_defines/statics.def"
#undef TALOS_XX_STATICS_DEFINE

    // and return the resulting instance
    return self;
}
