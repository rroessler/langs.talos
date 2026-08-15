#ifndef _XSIO_TASK_SCHEDULER_HPP
#define _XSIO_TASK_SCHEDULER_HPP

/// XSIO Includes
#include "xsio/forward/async.hpp"
#include "xsio/task/executor.hpp"

namespace XSIO::Task {

/// @brief Scheduler Loop Task.
class Scheduler : public Mixin<Scheduler> {
  //  PROPERTIES  //

  /// @brief Asynchronous runtime manager.
  Async::Manager *m_runtime;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a loop instance.
   * @param runtime               Runtime manager.
   */
  explicit Scheduler(Async::Manager *runtime) : m_runtime(runtime) {}

protected:
  //  PRIVATE METHODS  //

  /// @brief Handles the scheduling loop.
  $_NORETURN void m_execute() final;

  /**
   * @brief Handles when acquisitions fail.
   * @param processor             Processor to stall.
   */
  void m_busy(Virtual::Processor *processor);

  /**
   * @brief Handles incoming threads.
   * @param thread                Thread to fulfill.
   */
  void m_acquired(Virtual::Thread *thread, Virtual::Processor *processor);
};

} // namespace XSIO::Task

#endif
