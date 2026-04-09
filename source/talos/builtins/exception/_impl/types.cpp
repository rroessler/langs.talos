/// Talos Modules
#include "talos/type/builder.hpp"

/// Builtin Inlines
#include "talos/builtins/_inline/defines.ipp"

/// Forward Declarations
$_FWD(Talos::Builtins, namespace TB = Type::Builder)

//  TYPEDEFS  //

#define TALOS_XX_FIELDS_DEFINE(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_FIELDS(Object::Exception) {
#include "talos/builtins/exception/_defines/fields.def"
};
#undef TALOS_XX_FIELDS_DEFINE

#define TALOS_XX_STATICS_DEFINE(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_STATICS(Object::Exception) {
#include "talos/builtins/exception/_defines/statics.def"
};
#undef TALOS_XX_STATICS_DEFINE

//  PUBLIC METHODS  //

Talos::Type::Erased TALOS_BUILTIN_TRAITS(Object::Exception)::typing() { return prototype()->instantiate(); }

TALOS_MM_BUILTIN_FTYPE(Object::Exception, name) { return { TB::function(TB::string()) }; }
TALOS_MM_BUILTIN_FTYPE(Object::Exception, message) { return { TB::function(TB::string()) }; }

TALOS_MM_BUILTIN_STYPE(Object::Exception, from) {
    auto format = TB::optional(TB::string());
    auto args = TB::arguments(format, TB::any());
    return { TB::variadic(typing(), args) };
}

TALOS_MM_BUILTIN_STYPE(Object::Exception, named) {
    auto format = TB::optional(TB::string());  // prepare format
    auto args = TB::arguments(TB::string(), format, TB::any());
    return { TB::variadic(typing(), args) };  // and bind now
}

//  PRIVATE METHODS  //

void TALOS_BUILTIN_TRAITS(Object::Exception)::m_typedefs(Type::World* globals) {
    // prepare the prototype to be constructed
    auto proto = prototype();
    auto& fields = proto->fields();
    auto& statics = proto->statics();

#define TALOS_XX_FIELDS_DEFINE(N, ...) fields.emplace(#N, Field::N());
#include "talos/builtins/exception/_defines/fields.def"
#undef TALOS_XX_FIELDS_DEFINE

#define TALOS_XX_STATICS_DEFINE(N, ...) statics.emplace(#N, Static::N());
#include "talos/builtins/exception/_defines/statics.def"
#undef TALOS_XX_STATICS_DEFINE

    // and assign the resulting entity to be used
    globals->types().declare(name(), typing());
    globals->values().declare(name(), proto);
}
