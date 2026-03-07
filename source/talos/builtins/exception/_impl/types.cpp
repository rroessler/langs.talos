/// Talos Modules
#include "talos/type/builder.hpp"

/// Forward Declarations
$_FWD(namespace TB = Type::Builder, Talos::Builtins)

//  TYPEDEFS  //

#define X(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_FIELDS(Object::Exception) {
    TALOS_XX_FIELDS_EXCEPTION(X)
};
#undef X

#define X(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_STATICS(Object::Exception) {
    TALOS_XX_STATICS_EXCEPTION(X)
};
#undef X

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

#define X(N, ...) { #N, Field::N() },
    proto->fields() = $::Record<Type::Entity>({ TALOS_XX_FIELDS_EXCEPTION(X) });
#undef X

#define X(N, ...) { #N, Static::N() },
    proto->statics() = $::Record<Type::Entity>({ TALOS_XX_STATICS_EXCEPTION(X) });
#undef X

    // and assign the resulting entity to be used
    globals->types().declare(name(), typing());
    globals->values().declare(name(), proto);
}
