/// Talos Modules
#include "talos/type/builder.hpp"

/// Forward Declarations
$_FWD(namespace TB = Type::Builder, Talos::Builtins)

//  TYPEDEFS  //

#define X(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_FIELDS(Value::Symbol) {
    TALOS_XX_FIELDS_SYMBOL(X)
};
#undef X

#define X(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_STATICS(Value::Symbol) {
    TALOS_XX_STATICS_SYMBOL(X)
};
#undef X

//  PUBLIC METHODS  //

Talos::Type::Erased TALOS_BUILTIN_TRAITS(Value::Symbol)::typing() { return prototype()->instantiate(); }

TALOS_MM_BUILTIN_FTYPE(Value::Symbol, hash) { return { TB::function(TB::number()) }; }
TALOS_MM_BUILTIN_STYPE(Value::Symbol, from) { return { TB::function(TB::symbol(), TB::arguments(TB::any())) }; }

//  PRIVATE METHODS  //

void TALOS_BUILTIN_TRAITS(Value::Symbol)::m_typedefs(Type::World* globals) {
    // prepare the prototype to be used
    auto proto = prototype();

#define X(N, ...) { #N, Field::N() },
    proto->fields() = $::Record<Type::Entity>({ TALOS_XX_FIELDS_SYMBOL(X) });
#undef X

#define X(N, ...) { #N, Static::N() },
    proto->statics() = { TALOS_XX_STATICS_SYMBOL(X) };
#undef X

    // and declare the types to be used now
    globals->types().declare(name(), typing());
    globals->values().declare(name(), proto);
}
