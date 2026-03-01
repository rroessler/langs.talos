/// Forge Modules
#include "forge/type/builder.hpp"

/// Forward Declarations
$_FWD(namespace TB = Type::Builder, Forge::Builtins)

//  PRIVATE METHODS  //

void FORGE_BUILTIN_TRAITS(Builtins::Custom::Todo)::m_typedefs(Type::World* globals) {
    auto arguments = TB::arguments(TB::optional(TB::string()));
    auto signature = TB::function(TB::never(), arguments);

    globals->types().declare(name(), TB::never());
    globals->values().declare(name(), signature);
}
