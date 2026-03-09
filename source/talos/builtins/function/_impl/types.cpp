/// Talos Modules
#include "talos/type/builder.hpp"

/// Forward Declarations
$_FWD(Talos::Builtins, namespace TB = Type::Builder)

//  TYPEDEFS  //

#define X(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_FIELDS(Function::Dynamic) {
    TALOS_XX_FIELDS_FUNCTION(X)
};
#undef X

#define X(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_STATICS(Function::Dynamic) {
    TALOS_XX_STATICS_FUNCTION(X)
};
#undef X

//  PUBLIC METHODS  //

Talos::Type::Erased TALOS_BUILTIN_TRAITS(Function::Dynamic)::typing() { return TB::variadic(); }

TALOS_MM_BUILTIN_FTYPE(Function::Dynamic, arity) { return { TB::function(TB::number()) }; }
TALOS_MM_BUILTIN_FTYPE(Function::Dynamic, adicity) { return { TB::function(TB::number()) }; }

TALOS_MM_BUILTIN_FTYPE(Function::Dynamic, receiver) { return { TB::function(TB::any()) }; }
TALOS_MM_BUILTIN_FTYPE(Function::Dynamic, bind) { return { TB::function(TB::variadic(), TB::arguments(TB::any())) }; }

TALOS_MM_BUILTIN_STYPE(Function::Dynamic, limit) { return { TB::function(TB::number()) }; }

TALOS_MM_BUILTIN_STYPE(Function::Dynamic, call) {
    auto F = TB::constraint("F", TB::variadic());
    auto signature = TB::invocation(F, false);
    return { TB::generic(signature, TB::parameters(F)) };
}

TALOS_MM_BUILTIN_STYPE(Function::Dynamic, apply) {
    auto passthrough = TB::optional(TB::list(TB::any()));
    auto arguments = TB::arguments(TB::variadic(), passthrough);
    return { TB::function(TB::any(), arguments) };
}

//  PRIVATE METHODS  //

void TALOS_BUILTIN_TRAITS(Function::Dynamic)::m_typedefs(Type::World* globals) {
    // prepare the prototype to be constructed
    auto proto = prototype();

#define X(N, ...) { #N, Field::N() },
    proto->fields() = $::Record<Type::Entity>({ TALOS_XX_FIELDS_FUNCTION(X) });
#undef X

#define X(N, ...) { #N, Static::N() },
    proto->statics() = { TALOS_XX_STATICS_FUNCTION(X) };
#undef X

    // and assign the resulting entity to be used
    globals->types().declare(name(), typing());
    globals->values().declare(name(), proto);
}
