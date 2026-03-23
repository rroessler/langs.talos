/// Talos Modules
#include "talos/type/builder.hpp"

/// Forward Declarations
$_FWD(Talos::Builtins, namespace TB = Type::Builder)

//  PROPERTIES  //

/// @brief The core prototype constraint.
static auto g_T = Talos::Builtins::TB::constraint("T", Talos::Builtins::TB::any(), Talos::Builtins::TB::any());

//  PUBLIC METHODS  //

Talos::Type::Erased TALOS_BUILTIN_TRAITS(Builtins::Custom::Maybe)::typing() {
    return TB::generic(TB::maybe(g_T), TB::parameters(g_T));
}

//  PRIVATE METHODS  //

void TALOS_BUILTIN_TRAITS(Builtins::Custom::Maybe)::m_typedefs(Type::World* globals) {
    // assign the resulting entity to be used
    globals->types().declare(name(), typing());
}
