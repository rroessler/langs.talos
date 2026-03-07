/// Talos Modules
#include "talos/type/builder.hpp"

/// Builtin Modules
#include "talos/builtins/_inline/builtins.ipp"

//  PRIVATE METHODS  //

void TALOS_BUILTIN_TRAITS(Builtins::Custom::Intrinsics)::m_typedefs(Type::World* globals) {
    globals->types().declare("Any", $::New().shared<Type::Any>());
    globals->types().declare("Never", $::New().shared<Type::Never>());
}
