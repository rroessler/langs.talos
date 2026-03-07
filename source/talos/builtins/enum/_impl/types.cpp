/// Talos Modules
#include "talos/type/builder.hpp"

/// Forward Declarations
$_FWD(namespace TB = Type::Builder, Talos::Builtins)

//  TYPEDEFS  //

#define X(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_FIELDS(Object::Enum) {
    TALOS_XX_FIELDS_ENUM(X)
};
#undef X

#define X(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_STATICS(Object::Enum) {
    TALOS_XX_STATICS_ENUM(X)
};
#undef X

//  PUBLIC METHODS  //

TALOS_MM_BUILTIN_STYPE(Object::Enum, name) {
    auto E = TB::constraint("E");
    auto arguments = TB::arguments(E, TB::number());
    auto signature = TB::function(TB::string(), arguments);
    return { TB::generic(signature, TB::parameters(E)) };
}

TALOS_MM_BUILTIN_STYPE(Object::Enum, label) {
    auto E = TB::constraint("E");
    auto arguments = TB::arguments(E, TB::number());
    auto signature = TB::function(TB::string(), arguments);
    return { TB::generic(signature, TB::parameters(E)) };
}

TALOS_MM_BUILTIN_STYPE(Object::Enum, value) {
    auto E = TB::constraint("E");
    auto arguments = TB::arguments(E, TB::number());
    auto signature = TB::function(TB::number(), arguments);
    return { TB::generic(signature, TB::parameters(E)) };
}

//  PRIVATE METHODS  //

void TALOS_BUILTIN_TRAITS(Object::Enum)::m_typedefs(Type::World* globals) {
    // prepare the prototype to be constructed
    auto proto = prototype();
    auto instance = proto->instantiate();

    // update the underlying prototype now to be numeric
    proto->super() = Traits<Number::Tagged>::prototype();

#define X(N, ...) { #N, Static::N() },
    proto->statics() = { TALOS_XX_STATICS_ENUM(X) };
#undef X

    // and assign the resulting entity to be used
    globals->types().declare(name(), instance);
    globals->values().declare(name(), proto);
}
