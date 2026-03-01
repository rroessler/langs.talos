/// Forge Modules
#include "forge/type/builder.hpp"

/// Forward Declarations
$_FWD(namespace TB = Type::Builder, Forge::Builtins)

//  TYPEDEFS  //

#define X(N, ...) static Type::Entity N();
struct FORGE_BUILTIN_FIELDS(Value::Symbol) {
    FORGE_XX_FIELDS_SYMBOL(X)
};
#undef X

#define X(N, ...) static Type::Entity N();
struct FORGE_BUILTIN_STATICS(Value::Symbol) {
    FORGE_XX_STATICS_SYMBOL(X)
};
#undef X

//  PUBLIC METHODS  //

Forge::Type::Erased FORGE_BUILTIN_TRAITS(Value::Symbol)::typing() { return prototype()->instantiate(); }

FORGE_MM_BUILTIN_FTYPE(Value::Symbol, hash) { return { TB::function(TB::number()) }; }
FORGE_MM_BUILTIN_STYPE(Value::Symbol, from) { return { TB::function(TB::symbol(), TB::arguments(TB::any())) }; }

//  PRIVATE METHODS  //

void FORGE_BUILTIN_TRAITS(Value::Symbol)::m_typedefs(Type::World* globals) {
    // prepare the prototype to be used
    auto proto = prototype();

#define X(N, ...) { #N, Field::N() },
    proto->fields() = $::Record<Type::Entity>({ FORGE_XX_FIELDS_SYMBOL(X) });
#undef X

#define X(N, ...) { #N, Static::N() },
    proto->statics() = { FORGE_XX_STATICS_SYMBOL(X) };
#undef X

    // and declare the types to be used now
    globals->types().declare(name(), typing());
    globals->values().declare(name(), proto);
}
