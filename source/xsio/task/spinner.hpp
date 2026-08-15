#ifndef _XSIO_TASK_SPINNER_HPP
#define _XSIO_TASK_SPINNER_HPP

/// XSIO Includes
#include "xsio/async/scheduler.hpp"
#include "xsio/task/executor.hpp"
#include "xsio/virtual/thread.hpp"

namespace XSIO::Task {

/// @brief Constructs a virtualized spinner.
class Spinner : public $::Spinner::Abstract {
  //  TYPEDEFS  //

  /// @brief Allow the internal worker access.
  friend class Worker;

  /// @brief Allow the manager internal access.
  friend class Async::Manager;

  /// @brief Spinner Worker Thread.
  class Worker : public Mixin<Worker> {
    //  PROPERTIES  //

    /// @brief The bound spinner instance.
    $::Shared::Pointer<Spinner> m_self;

  public:
    //  CONSTRUCTORS  //

    /**
     * @brief Constructs a worker instance.
     * @param self              Spinner value.
     */
    explicit Worker(const $::Shared::Pointer<Spinner> &self) : m_self(self) {}

  protected:
    //  PRIVATE METHODS  //

    /// @brief Handles executing the spinner.
    inline void m_execute() final { m_self->m_loop(); }
  };

  //  PROPERTIES  //

  /// @brief Internal spinner worker.
  Worker *m_worker = nullptr;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Handles constructing a spinner.
   * @param options                 Options to use.
   */
  explicit Spinner(const $::String::Buffer &text) : Spinner({.suffix = text}) {}
  explicit Spinner(const $::Spinner::Options &options = {}) : Abstract(options) {}

protected:
  //  PRIVATE METHODS  //

  /// @brief Handles running the sleep instance.
  inline void m_sleep() const noexcept final { m_worker->thread()->sleep(options().tick); }

  /**
   * @brief Starts scheduling the spinner instance.
   * @param scheduler             Asynchronous scheduler.
   */
  inline void m_schedule(Async::Scheduler *scheduler) { m_worker = scheduler->schedule<Worker>(m_as<Spinner>()); }
};

} // namespace XSIO::Task

#endif
