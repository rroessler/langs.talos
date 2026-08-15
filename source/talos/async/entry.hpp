#ifndef _TALOS_ASYNC_ENTRY_HPP
#define _TALOS_ASYNC_ENTRY_HPP

/// Talos Includes
#include "talos/async/service.hpp"
#include "talos/runtime/executor.hpp"

namespace Talos::Async {

/// @brief Describes a main-entry isolate.
struct $_ABSTRACT Entry : public Runtime::Executor {
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a main-isolate.
   * @param args              Executor arguments.
   */
  template <class... As> explicit Entry(As &&...args) : Executor(std::forward<As>(args)...) {
    service<Service>()->m_isolate = this;
  }
};

} // namespace Talos::Async

#endif
