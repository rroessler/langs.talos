#ifndef _TALOS_BUNDLE_SERVICE_HPP
#define _TALOS_BUNDLE_SERVICE_HPP

/// Talos Includes
#include "talos/bundle/options.hpp"

namespace Talos::Bundle {

/// @brief Core Runtime Service.
class Service : public XI::Singleton {
  //  PROPERTIES  //

  /// @brief Available services container.
  XI::Container *m_services;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a bundling service.
   * @param services                  Services container.
   */
  explicit Service();
  explicit Service(XI::Container *services);

  //  PUBLIC METHODS  //

  /**
   * @brief Handles bundling the runtime.
   * @param options                   Bundle options.
   */
  int32_t bundle(const Options &options);
};

} // namespace Talos::Bundle

#endif
