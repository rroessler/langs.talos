/// Talos Modules
#include "talos/type/builder.hpp"

/// Builtin Inlines
#include "talos/builtins/_inline/defines.ipp"

/// Forward Declarations
$_FWD(Talos::Builtins, namespace TB = Type::Builder)

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_FIELDS(Value::Symbol) {
#include "talos/builtins/symbol/_defines/fields.def"
};
#undef TALOS_XX_FIELDS_DEFINE

#define TALOS_XX_STATICS_DEFINE(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_STATICS(Value::Symbol) {
#include "talos/builtins/symbol/_defines/statics.def"
};
#undef TALOS_XX_STATICS_DEFINE

//  PUBLIC METHODS  //

Talos::Type::Erased TALOS_BUILTIN_TRAITS(Value::Symbol)::typing() { return prototype()->instantiate(); }

TALOS_MM_BUILTIN_FTYPE(Value::Symbol, hash) { return { TB::function(TB::number()) }; }
TALOS_MM_BUILTIN_STYPE(Value::Symbol, from) { return { TB::function(TB::symbol(), TB::arguments(TB::any())) }; }

//  PRIVATE METHODS  //

void TALOS_BUILTIN_TRAITS(Value::Symbol)::m_typedefs(Type::World* globals) {
    // prepare the prototype to be used
    auto proto = prototype();
    auto& fields = proto->fields();
    auto& statics = proto->statics();

#define TALOS_XX_FIELDS_DEFINE(N, ...) fields.emplace(#N, Field::N());
#include "talos/builtins/symbol/_defines/fields.def"
#undef TALOS_XX_FIELDS_DEFINE

#define TALOS_XX_STATICS_DEFINE(N, ...) statics.emplace(#N, Static::N());
#include "talos/builtins/symbol/_defines/statics.def"
#undef TALOS_XX_STATICS_DEFINE

    // and declare the types to be used now
    globals->types().declare(name(), typing());
    globals->values().declare(name(), proto);
}
