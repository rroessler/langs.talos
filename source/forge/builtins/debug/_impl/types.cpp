/// Forge Modules
#include "forge/type/builder.hpp"

/// Forward Declarations
$_FWD(namespace TB = Type::Builder, Forge::Builtins)

//  PRIVATE METHODS  //

void FORGE_BUILTIN_TRAITS(Builtins::Custom::Debug)::m_typedefs(Type::World* globals) {
    // bind all the underlying fields to be used now
#define X(N, ...) { #N, { TB::variadic(TB::none()) } },
    auto fields = $::Record<Type::Entity>({ FORGE_XX_FIELDS_DEBUG(X) });
#undef X

    // expose the "Debug" protocol only as a value
    globals->values().declare(name(), TB::interface(name(), fields));
}
