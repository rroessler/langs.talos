/// Talos Modules
#include "talos/type/builder.hpp"

/// Forward Declarations
$_FWD(Talos::Builtins, namespace TB = Type::Builder)

//  PRIVATE METHODS  //

void TALOS_BUILTIN_TRAITS(Builtins::Custom::Todo)::m_typedefs(Type::World* globals) {
    auto arguments = TB::arguments(TB::optional(TB::string()));
    auto signature = TB::function(TB::never(), arguments);

    globals->types().declare(name(), TB::never());
    globals->values().declare(name(), signature);
}
