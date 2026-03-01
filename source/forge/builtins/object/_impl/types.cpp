/// Forge Modules
#include "forge/type/builder.hpp"

/// Forward Declarations
$_FWD(namespace TB = Type::Builder, Forge::Builtins)

//  PUBLIC METHODS  //

Forge::Type::Erased FORGE_BUILTIN_TRAITS(Object::Instance)::typing() { return TB::object(); }

//  PRIVATE METHODS  //

void FORGE_BUILTIN_TRAITS(Object::Instance)::m_typedefs(Type::World* globals) {
    // prepare the baseline object types
    globals->types().declare(name(), typing());
    globals->values().declare(name(), prototype());

    /// TODO: also expose a record typing to be used
}
