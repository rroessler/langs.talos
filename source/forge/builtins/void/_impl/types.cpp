/// Forge Modules
#include "forge/type/builder.hpp"

/// Forward Declarations
$_FWD(namespace TB = Type::Builder, Forge::Builtins)

//  PUBLIC METHODS  //

Forge::Type::Erased FORGE_BUILTIN_TRAITS(Value::Void)::typing() { return TB::none(); }

//  PRIVATE METHODS  //

void FORGE_BUILTIN_TRAITS(Value::Void)::m_typedefs(Type::World* globals) {
    globals->types().declare(name(), typing());
    globals->values().declare(name(), typing());
}
