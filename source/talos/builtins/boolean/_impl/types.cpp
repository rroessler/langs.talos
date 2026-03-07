/// Talos Modules
#include "talos/type/builder.hpp"

/// Forward Declarations
$_FWD(namespace TB = Type::Builder, Talos::Builtins)

//  TYPEDEFS  //

#define X(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_STATICS(Value::Boolean) {
    TALOS_XX_STATICS_BOOLEAN(X)
};
#undef X

//  PUBLIC METHODS  //

Talos::Type::Erased TALOS_BUILTIN_TRAITS(Value::Boolean)::typing() { return prototype()->instantiate(); }

TALOS_MM_BUILTIN_STYPE(Value::Boolean, from) { return { TB::function(TB::boolean(), TB::arguments(TB::any())) }; }
TALOS_MM_BUILTIN_STYPE(Value::Boolean, parse) {
    Type::Entity source = TB::string(), sensitivity = TB::optional(TB::boolean());
    return { TB::function(TB::boolean(), TB::arguments(source, sensitivity)) };
}

//  PRIVATE METHODS  //

void TALOS_BUILTIN_TRAITS(Value::Boolean)::m_typedefs(Type::World* globals) {
    // get the underlying prototype instance
    auto proto = prototype();

#define X(N, ...) { #N, Static::N() },
    proto->statics() = { TALOS_XX_STATICS_BOOLEAN(X) };
#undef X

    // prepare the baseline typing to be used
    globals->types().declare(name(), typing());
    globals->values().declare(name(), proto);

    // and generate the "True" and "False" typings as well
    globals->values().declare("True", typing());
    globals->values().declare("False", typing());
}
