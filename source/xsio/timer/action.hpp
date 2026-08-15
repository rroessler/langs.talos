#ifndef _XSIO_TIMER_ACTION_HPP
#define _XSIO_TIMER_ACTION_HPP

/// XSIO Includes
#include "xsio/forward/timer.hpp"
#include "xsio/forward/virtual.hpp"

namespace XSIO::Timer {

/// @brief Timer Action Abstraction.
template <class T> using Abstract = $::RTTI::Mixin<T, Action>;

/// @brief Action Callback Handler.
using Callback = $::Shared::Functor<void(Virtual::Thread *, Virtual::Processor *)>;

/// @brief Timer Action Base.
struct $_ABSTRACT Action : public $::RTTI::Dynamic {
  //  CONSTRUCTORS  //

  /// @brief Virtual abstract destructor.
  virtual ~Action() = default;

  //  PUBLIC METHODS  //

  /**
   * @brief Handles executing a timer action.
   * @param thread                Thread instance.
   * @param processor             Processor instance.
   */
  virtual void execute(Virtual::Thread *thread, Virtual::Processor *processor) = 0;
};

} // namespace XSIO::Timer

#endif
