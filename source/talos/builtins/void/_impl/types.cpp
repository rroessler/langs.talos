/// Talos Modules
#include "talos/type/builder.hpp"

/// Forward Declarations
$_FWD(namespace TB = Type::Builder, Talos::Builtins)

//  PUBLIC METHODS  //

Talos::Type::Erased TALOS_BUILTIN_TRAITS(Value::Void)::typing() { return TB::none(); }

//  PRIVATE METHODS  //

void TALOS_BUILTIN_TRAITS(Value::Void)::m_typedefs(Type::World* globals) {
    globals->types().declare(name(), typing());
    globals->values().declare(name(), typing());
}
