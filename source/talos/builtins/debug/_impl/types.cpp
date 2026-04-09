/// Talos Modules
#include "talos/type/builder.hpp"

/// Builtins Inlines
#include "talos/builtins/_inline/defines.ipp"

/// Forward Declarations
$_FWD(Talos::Builtins, namespace TB = Type::Builder)

//  PRIVATE METHODS  //

void TALOS_BUILTIN_TRAITS(Builtins::Custom::Debug)::m_typedefs(Type::World* globals) {
    // prepare the fields to be used
    auto fields = $::Record<Type::Entity>();

    // bind all the underlying fields to be used now
#define TALOS_XX_FIELDS_DEFINE(N, ...) fields.emplace(#N, TB::variadic(TB::none()));
#include "talos/builtins/debug/_defines/fields.def"
#undef TALOS_XX_FIELDS_DEFINE

    // expose the "Debug" protocol only as a value
    globals->values().declare(name(), TB::interface(name(), fields));
}
