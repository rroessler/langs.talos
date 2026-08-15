#ifndef _XSIO_VIRTUAL_TIMEOUT_HPP
#define _XSIO_VIRTUAL_TIMEOUT_HPP

/// XSIO Includes
#include "xsio/async/scheduler.hpp"
#include "xsio/task/deferred.hpp"
#include "xsio/task/executor.hpp"
#include "xsio/timer/action.hpp"
#include "xsio/timer/token.hpp"
#include "xsio/virtual/thread.hpp"

namespace XSIO::Task {

/// @brief Constructs a virtualized timeout.
class Timeout {
  //  TYPEDEFS  //

  /// @brief The underlying callback handler.
  using Callback = Timer::Callback;

  /// @brief The underlying deferred typing.
  using Deferred = Task::Deferred<Timer::Token>;

  /// @brief Handles executing timer callbacks.
  class Action : public Timer::Abstract<Action> {
    //  PROPERTIES  //

    /// @brief The bound timeout instance.
    Timeout *m_self;

  public:
    //  CONSTRUCTORS  //

    /**
     * @brief Constructs a timeout action.
     * @param self              Timeout value.
     */
    explicit Action(Timeout *self) : m_self(self) {}

    //  PUBLIC METHODS  //

    /**
     * @brief Handles executing the timeout.
     * @param thread            Virtual thread.
     * @param processor         Virtual processor.
     */
    inline void execute(Virtual::Thread *thread, Virtual::Processor *processor) final {
      m_self->m_callback(thread, processor); // execute the bound callback now
    }
  };

  /// @brief Timeout Worker Thread.
  class Worker : public Task::Mixin<Worker> {
    //  PROPERTIES  //

    /// @brief The bound timeout instance.
    Timeout *m_self;

  public:
    //  CONSTRUCTORS  //

    /**
     * @brief Constructs a timeout worker.
     * @param self              Timeout value.
     */
    explicit Worker(Timeout *self) : m_self(self) {}

  protected:
    //  PRIVATE METHODS  //

    /// @brief Handles executing the timeout.
    inline void m_execute() final {
      // get the underlying timers cache to be used
      auto *timers = m_thread->worker()->processor()->timers();

      // construct the action instance to be used
      auto action = $::Unique::New<Action>(m_self);

      // prepare the timeout token now
      auto token = timers->schedule(m_self->m_timestamp, m_self->m_callback);

      // update the internal token reference
      m_self->m_token.resolve(m_thread, token);
    }
  };

  //  PROPERTIES  //

  /// @brief Internal spinner worker.
  Worker *m_worker = nullptr;

  /// @brief Timestamp to wait until.
  Timer::Point m_timestamp = {};

  /// @brief The available token instance.
  Deferred m_token = Deferred();

  /// @brief The underlying timeout callback.
  Timer::Callback m_callback = [](Virtual::Thread *, Virtual::Processor *) {};

public:
  //  CONSTRUCTORS  //

  /// @brief Default timeout constructor.
  explicit Timeout() = default;

  /**
   * @brief Constructs a timeout.
   * @param scheduler             Scheduler to use.
   * @param duration              Timeout duration.
   * @param callback              Callback to run.
   */
  explicit Timeout(Async::Scheduler *scheduler, const Timer::Ticks &duration, Callback &&callback) :
      Timeout(scheduler, Timer::Point() + duration, std::move(callback)) {}

  /**
   * @brief Constructs a timeout.
   * @param scheduler             Scheduler to use.
   * @param timestamp             Timeout timestamp.
   * @param callback              Callback to run.
   */
  explicit Timeout(Async::Scheduler *scheduler, const Timer::Point &timestamp, Callback &&callback) :
      m_timestamp(timestamp), m_callback(std::move(callback)) {
    m_worker = scheduler->schedule<Worker>(this);
  }

  //  PUBLIC METHODS  //

  /**
   * @brief Gets the underlying timeout token.
   * @param thread                Virtual thread.
   */
  inline constexpr Timer::Token token(Virtual::Thread *thread) noexcept { return *m_token.await(thread); }

  /**
   * @brief Handles cancelling the underlying token.
   * @param thread                Virtual thread.
   */
  inline constexpr bool cancel(Virtual::Thread *thread) noexcept { return token(thread).cancel(); }
};

} // namespace XSIO::Task

#endif
