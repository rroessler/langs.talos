#ifndef _TALOS_CRATE_SERVICE_HPP
#define _TALOS_CRATE_SERVICE_HPP

/// Talos Includes
#include "talos/crate/constants.hpp"
#include "talos/crate/manifest.hpp"
#include "talos/value/common.hpp"

namespace Talos::Crate {

/// @brief Crate Runtime Service.
class Service : public XI::Singleton {
  //  PROPERTIES  //

  /// @brief Crates mutex.
  mutable $::Mutex::Auto m_mutex;

  /// @brief All resolved crates.
  $::Map::Dict<$::Unique::Pointer<Manifest>> m_storage = {};

public:
  //  CONSTRUCTORS  //

  /// @brief Allow default construction.
  explicit Service() = default;

  //  PUBLIC METHODS  //

  /**
   * @brief Handles validating file-paths.
   * @param resource                  Resource to resolve.
   */
  bool validate(const $::FS::Path &resource);

  /**
   * @brief Handles getting a cached crate resource package.
   * @param resource                  Resource to resolve.
   */
  const Manifest *resolve(const $::FS::Path &resource);
  const Manifest *resolve(const $::URI::View &resource);

  /**
   * @brief Handles getting dynamic crate values.
   * @param isolate                   Thread isolate.
   * @param name                      Library name.
   */
  Value::Any dylib(Runtime::Isolate *isolate, const $::String::View &name) const noexcept;
};

} // namespace Talos::Crate

#endif
