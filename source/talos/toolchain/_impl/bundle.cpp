/// Talos Modules
#include "talos/toolchain/bundle.hpp"
#include "talos/bundle/archive.hpp"
#include "talos/bundle/service.hpp"
#include "talos/runtime/container.hpp"

//  PUBLIC METHODS  //

int32_t Talos::Toolchain::lint(const Runtime::Options& runtime) {
    return bundle(Bundle::Options(std::false_type()), runtime);
}

int32_t Talos::Toolchain::bundle(const Bundle::Options& options, const Runtime::Options& runtime) {
    auto* services = $::Global::get<Runtime::Container>(runtime);
    return services->emplace<Bundle::Service>()->bundle(options);
}
