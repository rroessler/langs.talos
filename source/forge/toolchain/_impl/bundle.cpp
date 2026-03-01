/// Forge Modules
#include "forge/toolchain/bundle.hpp"
#include "forge/bundle/archive.hpp"
#include "forge/bundle/service.hpp"
#include "forge/runtime/container.hpp"

//  PUBLIC METHODS  //

int32_t Forge::Toolchain::lint(const Runtime::Options& runtime) {
    return bundle(Bundle::Options(std::false_type()), runtime);
}

int32_t Forge::Toolchain::bundle(const Bundle::Options& options, const Runtime::Options& runtime) {
    auto* services = $::Global::get<Runtime::Container>(runtime);
    return services->emplace<Bundle::Service>()->bundle(options);
}
