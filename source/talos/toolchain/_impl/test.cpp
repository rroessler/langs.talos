/// Talos Includes
#include "talos/toolchain/test.hpp"
#include "talos/testing/service.hpp"
#include "talos/testing/storage.hpp"
#include "talos/toolchain/launch.hpp"

//  PUBLIC METHODS  //

int32_t Talos::Toolchain::test(const Runtime::Options &options) {
  return bootstrap(options)->load<Testing::Service>()->spawn();
}
