/// Talos Includes
#include "talos/toolchain/serve.hpp"
#include "talos/server/connection.hpp"
#include "talos/toolchain/launch.hpp"

//  PUBLIC METHODS  //

int32_t Talos::Toolchain::serve(const Runtime::Options &options) {
  return bootstrap(options)->load<Server::Connection>()->listen();
}
