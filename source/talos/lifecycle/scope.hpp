#ifndef _TALOS_LIFECYCLE_SCOPE_HPP
#define _TALOS_LIFECYCLE_SCOPE_HPP

/// Talos Includes
#include "talos/forward/lifecycle.hpp"
#include "talos/forward/runtime.hpp"

namespace Talos::Lifecycle {

/// @brief Scoped Lifecycle Handler.
class Scope : public XI::Transient {
  //  PROPERTIES  //

  /// @brief The lifecycle service.
  Service *m_lifecycle;

  /// @brief Bound isolate instance.
  Runtime::Isolate *m_isolate;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a lifecycle scoping.
   * @param services          Services container.
   * @param isolate           Runtime isolate.
   */
  explicit Scope(Runtime::Isolate *isolate = nullptr);
  explicit Scope(XI::Container *services, Runtime::Isolate *isolate = nullptr);

  /// @brief Handles destructing the scoping.
  ~Scope();
};

} // namespace Talos::Lifecycle

#endif
