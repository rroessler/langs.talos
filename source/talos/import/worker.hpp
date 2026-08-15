#ifndef _TALOS_IMPORT_WORKER_HPP
#define _TALOS_IMPORT_WORKER_HPP

/// Talos Includes
#include "talos/forward/async.hpp"
#include "talos/module/abstract.hpp"

namespace Talos::Import {

/// @brief Import Worker Result.
using Result = XSIO::Task::Deferred<Module::Abstract *>;

/// @brief Import Worker.
class Worker : public Async::Task<Worker> {
  //  PROPERTIES  //

  /// @brief Resource to import.
  $::URI::Buffer m_resource = {};

  /// @brief Import modules service.
  Service *m_modules = nullptr;

  /// @brief Encapsulated thenable instance.
  Result *m_deferred = nullptr;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs an import worker.
   * @param services                Services container.
   * @param deferred                Deferred result.
   * @param resource                Resource to import.
   */
  explicit Worker(Result *deferred, const $::URI::Buffer &resource = {});
  explicit Worker(XI::Container *services, Result *deferred, const $::URI::Buffer &resource = {});

protected:
  //  PRIVATE METHODS  //

  /// @brief Handles importing the resource.
  void m_execute() final;
};

} // namespace Talos::Import

#endif
