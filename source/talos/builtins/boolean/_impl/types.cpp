/// Talos Modules
#include "talos/type/builder.hpp"

/// Builtin Inlines
#include "talos/builtins/_inline/defines.ipp"

/// Forward Declarations
$_FWD(Talos::Builtins, namespace TB = Type::Builder)

//  TYPEDEFS  //

#define TALOS_XX_STATICS_DEFINE(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_STATICS(Value::Boolean) {
#include "talos/builtins/boolean/_defines/statics.def"
};
#undef TALOS_XX_STATICS_DEFINE

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
    auto& statics = proto->statics();

    // define the underlying statics for booleans
#define TALOS_XX_STATICS_DEFINE(N, ...) statics.emplace(#N, Static::N());
#include "talos/builtins/boolean/_defines/statics.def"
#undef TALOS_XX_STATICS_DEFINE

    // prepare the baseline typing to be used
    globals->types().declare(name(), typing());
    globals->values().declare(name(), proto);

    // and generate the "True" and "False" typings as well
    globals->values().declare("True", typing());
    globals->values().declare("False", typing());
}
