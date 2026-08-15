/// Talos Includes
#include "talos/toolchain/bundle.hpp"
#include "talos/bundle/service.hpp"
#include "talos/runtime/container.hpp"
#include "talos/toolchain/launch.hpp"

//  PUBLIC METHODS  //

int32_t Talos::Toolchain::lint(const Runtime::Options &runtime) {
  return bundle(Bundle::Options(std::false_type()), runtime);
}

int32_t Talos::Toolchain::bundle(const Bundle::Options &options, const Runtime::Options &runtime) {
  return bootstrap(runtime)->load<Bundle::Service>()->bundle(options);
}
