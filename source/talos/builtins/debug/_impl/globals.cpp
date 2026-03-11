/// Talos Modules
#include "talos/member/factory.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/builtins.ipp"

//  TYPEDEFS  //

#define X(N, ...) static Value::Any N(Runtime::Isolate*, const Function::Arguments&);
struct TALOS_BUILTIN_FIELDS(Builtins::Custom::Debug) {
    TALOS_XX_FIELDS_DEBUG(X)
};
#undef X

//  PUBLIC METHODS  //

#define X(N, ...)                                                                \
    TALOS_MM_BUILTIN_FIELD(Builtins::Custom::Debug, N, , arguments) {            \
        return $::IO::N("{0}", fmt::join(arguments.span(), " ")), Value::Void(); \
    }

X(print)
X(eprint)
X(println)
X(eprintln)
#undef X

TALOS_MM_BUILTIN_FIELD(Builtins::Custom::Debug, breakpoint, , ) { $_ABORT("Unimplemented 'Debug.breakpoint'"); }

//  PRIVATE METHODS  //

Talos::Value::Any TALOS_BUILTIN_TRAITS(Builtins::Custom::Debug)::m_globals(Runtime::Isolate* isolate) {
    // construct the base object instance
    auto self = isolate->create<Object::Instance>();

// assign the necessary fields now
#define X(N, ...) self.fields().emplace(#N, Member::Factory::native(isolate, Field::N, name(), #N));
    TALOS_XX_FIELDS_DEBUG(X)
#undef X

    // and return the resulting instance
    return self;
}
