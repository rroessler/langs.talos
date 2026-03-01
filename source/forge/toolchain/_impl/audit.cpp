/// Forge Modules
#include "forge/toolchain/audit.hpp"
#include "forge/runtime/container.hpp"
#include "forge/type/analyzer.hpp"

//  PUBLIC METHODS  //

$::Ptr::Unique<Forge::Type::Context> Forge::Toolchain::audit(const Syntax::Tree *syntax, const Type::Options &options) {
    auto *services = options.services ? options.services : $::Global::get<Runtime::Container>();
    return services->get<Type::Analyzer>()->audit(syntax, options.reporter);
}
