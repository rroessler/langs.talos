/// Talos Modules
#include "talos/type/builder.hpp"

/// Forward Declarations
$_FWD(Talos::Builtins, namespace TB = Type::Builder)

//  PUBLIC METHODS  //

Talos::Type::Erased TALOS_BUILTIN_TRAITS(Object::Instance)::typing() { return TB::object(); }

//  PRIVATE METHODS  //

void TALOS_BUILTIN_TRAITS(Object::Instance)::m_typedefs(Type::World* globals) {
    // prepare the baseline object types
    globals->types().declare(name(), typing());
    globals->values().declare(name(), prototype());

    /// TODO: also expose a record typing to be used
}
