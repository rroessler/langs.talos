#ifndef _TALOS_ASYNC_SERVICE_HPP
#define _TALOS_ASYNC_SERVICE_HPP

/// Talos Includes
#include "talos/forward/async.hpp"
#include "talos/runtime/options.hpp"

namespace Talos::Async {

/// @brief Asynchronous Event-Loop Service.
class Service : public XI::Singleton, public XSIO::Async::Manager {
  //  TYPEDEFS  //

  /// @brief Allow main isolates internal access.
  friend struct Entry;

  //  PROPERTIES  //

  /// @brief The main runtime isolate.
  Runtime::Isolate *m_isolate = nullptr;

public:
  //  CONSTRUCTORS  //

  /// @brief Allow default construction.
  explicit Service() = default;

  /**
   * @brief Constructs an asynchronous manager.
   * @param services          Services container.
   */
  explicit Service(XI::Container *services) : Service(*services) {}
  explicit Service(const Runtime::Options *options) : Manager(&options->async) {}

  //  PUBLIC METHODS  //

  /// @brief Gets the main-runtime isolate.
  inline constexpr Runtime::Isolate *isolate() const noexcept { return m_isolate; }
};

} // namespace Talos::Async

#endif
