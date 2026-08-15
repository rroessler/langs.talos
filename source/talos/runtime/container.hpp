#ifndef _TALOS_RUNTIME_CONTAINER_HPP
#define _TALOS_RUNTIME_CONTAINER_HPP

/// Talos Includes
#include "talos/forward/runtime.hpp"

namespace Talos::Runtime {

/// @brief Runtime Services Container.
struct Container : public XI::Container {
  //  CONSTRUCTORS  //

  /// @brief Constructs a defaulted runtime container.
  explicit Container();

  /**
   * @brief Constructs a runtime container.
   * @param options                 Options to bind.
   */
  explicit Container(const Options &options);
};

} // namespace Talos::Runtime

#endif
