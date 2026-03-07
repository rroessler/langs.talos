/// Talos Modules
#include "talos/toolchain/audit.hpp"
#include "talos/runtime/container.hpp"
#include "talos/type/analyzer.hpp"

//  PUBLIC METHODS  //

$::Ptr::Unique<Talos::Type::Context> Talos::Toolchain::audit(const Syntax::Tree *syntax, const Type::Options &options) {
    auto *services = options.services ? options.services : $::Global::get<Runtime::Container>();
    return services->get<Type::Analyzer>()->audit(syntax, options.reporter);
}
