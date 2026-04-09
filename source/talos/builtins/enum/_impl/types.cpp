/// Talos Modules
#include "talos/type/builder.hpp"

/// Builtin Inlines
#include "talos/builtins/_inline/defines.ipp"

/// Forward Declarations
$_FWD(Talos::Builtins, namespace TB = Type::Builder)

//  TYPEDEFS  //

#define TALOS_XX_STATICS_DEFINE(N, ...) static Type::Entity N();
struct TALOS_BUILTIN_STATICS(Object::Enum) {
#include "talos/builtins/enum/_defines/statics.def"
};
#undef TALOS_XX_STATICS_DEFINE

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
    auto& statics = proto->statics();
    auto instance = proto->instantiate();

    // update the underlying prototype now to be numeric
    proto->super() = Traits<Number::Tagged>::prototype();

#define TALOS_XX_STATICS_DEFINE(N, ...) statics.emplace(#N, Static::N());
#include "talos/builtins/enum/_defines/statics.def"
#undef TALOS_XX_STATICS_DEFINE

    // and assign the resulting entity to be used
    globals->types().declare(name(), instance);
    globals->values().declare(name(), proto);
}
