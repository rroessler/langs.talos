#ifndef _TALOS_ASYNC_WORKER_HPP
#define _TALOS_ASYNC_WORKER_HPP

/// Talos Includes
#include "talos/async/future.hpp"
#include "talos/resource/frame.hpp"
#include "talos/runtime/executor.hpp"

namespace Talos::Async {

/// @brief Future Worker Isolate.
class Worker : public Runtime::Executor {
  //  PROPERTIES  //

  /// @brief Underlying resource frame (for backtraces)
  $::Unique::Pointer<Resource::Frame> m_caller = nullptr;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a future isolate.
   * @param services          Services container.
   * @param future            Future to bind.
   * @param trace             Resource trace.
   */
  explicit Worker(XI::Container *services, const Future &future) : Executor(services, future) {}
  explicit Worker(XI::Container *services, const Future &future, const Resource::Trace &trace) :
      Worker(services, future) {
    if (!trace.anonymous()) m_caller = $::Unique::New<Resource::Frame>(this, trace);
  }

protected:
  //  PRIVATE METHODS  //

  /// @brief Handles launching the runtime.
  void m_execute() final;
};

} // namespace Talos::Async

#endif
