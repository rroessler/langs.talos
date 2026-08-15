#ifndef _XSIO_SWITCH_CONTEXT_HPP
#define _XSIO_SWITCH_CONTEXT_HPP

/// XSIO Includes
#include "xsio/forward/async.hpp"
#include "xsio/forward/task.hpp"
#include "xsio/switch/transfer.hpp"
#include "xsio/virtual/state.hpp"

namespace XSIO::Switch {

/// @brief Callback for context switches.
using Callback = $::Unique::Functor<void(Virtual::Thread *, Virtual::Processor *)>;

/// @brief Context Switches.
struct Context : private $::Ensure::Static {
  //  PUBLIC METHODS  //

  /**
   * @brief Waits for the scheduler to acquire a worker.
   * @param loop                      Scheduler loop to wait.
   */
  static void yield_to_worker(Task::Scheduler *loop);

  /**
   * @brief Yields a worker to the scheduler.
   * @param worker                    Worker to yield.
   */
  static void yield_to_scheduler(Virtual::Worker *worker);

  /**
   * @brief Yields the scheduler to an acquired thread.
   * @param loop                      Scheduler loop to yield.
   * @param thread                    Thread to initialize.
   */
  static void yield_to_thread(Task::Scheduler *loop, Virtual::Thread *thread);

  /**
   * @brief Yields a thread to the scheduler.
   * @param thread                    Thread to yield.
   * @param state                     Next thread state.
   * @param callback                  Optional callback.
   */
  static void yield_to_scheduler(Virtual::Thread *thread, Virtual::State state);
  static void yield_to_scheduler(Virtual::Thread *thread, Virtual::State state, Callback &&callback);

  /**
   * @brief Waits for a thread callback.
   * @param thread                    Thread to await.
   * @param processor                 Virtual processor.
   */
  static void wait_for_thread(Virtual::Thread *thread, Virtual::Processor *processor);

private:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles a context-switching transfer.
   * @param transfer                  Transfer to occur.
   */
  $_NORETURN static void m_transfer(Transfer transfer);

  /**
   * @brief Handles allocating a thread-stack.
   * @param thread                    Thread to acquire onto.
   * @param worker                    Worker instance to bind.
   */
  static void m_allocate(Virtual::Thread *thread, Virtual::Worker *worker);
};

} // namespace XSIO::Switch

#endif
