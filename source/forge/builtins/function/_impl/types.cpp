/// Forge Modules
#include "forge/type/builder.hpp"

/// Forward Declarations
$_FWD(namespace TB = Type::Builder, Forge::Builtins)

//  TYPEDEFS  //

#define X(N, ...) static Type::Entity N();
struct FORGE_BUILTIN_FIELDS(Function::Dynamic) {
    FORGE_XX_FIELDS_FUNCTION(X)
};
#undef X

#define X(N, ...) static Type::Entity N();
struct FORGE_BUILTIN_STATICS(Function::Dynamic) {
    FORGE_XX_STATICS_FUNCTION(X)
};
#undef X

//  PUBLIC METHODS  //

Forge::Type::Erased FORGE_BUILTIN_TRAITS(Function::Dynamic)::typing() { return TB::variadic(); }

FORGE_MM_BUILTIN_FTYPE(Function::Dynamic, arity) { return { TB::function(TB::number()) }; }
FORGE_MM_BUILTIN_FTYPE(Function::Dynamic, adicity) { return { TB::function(TB::number()) }; }

FORGE_MM_BUILTIN_FTYPE(Function::Dynamic, receiver) { return { TB::function(TB::any()) }; }
FORGE_MM_BUILTIN_FTYPE(Function::Dynamic, bind) { return { TB::function(TB::variadic(), TB::arguments(TB::any())) }; }

FORGE_MM_BUILTIN_STYPE(Function::Dynamic, limit) { return { TB::function(TB::number()) }; }

FORGE_MM_BUILTIN_STYPE(Function::Dynamic, call) {
    auto F = TB::constraint("F", TB::variadic());
    auto signature = TB::invocation(F, false);
    return { TB::generic(signature, TB::parameters(F)) };
}

FORGE_MM_BUILTIN_STYPE(Function::Dynamic, apply) {
    auto passthrough = TB::optional(TB::list(TB::any()));
    auto arguments = TB::arguments(TB::variadic(), passthrough);
    return { TB::function(TB::any(), arguments) };
}

//  PRIVATE METHODS  //

void FORGE_BUILTIN_TRAITS(Function::Dynamic)::m_typedefs(Type::World* globals) {
    // prepare the prototype to be constructed
    auto proto = prototype();

#define X(N, ...) { #N, Field::N() },
    proto->fields() = $::Record<Type::Entity>({ FORGE_XX_FIELDS_FUNCTION(X) });
#undef X

#define X(N, ...) { #N, Static::N() },
    proto->statics() = { FORGE_XX_STATICS_FUNCTION(X) };
#undef X

    // and assign the resulting entity to be used
    globals->types().declare(name(), typing());
    globals->values().declare(name(), proto);
}
