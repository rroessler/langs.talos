/// XSIO Includes
#include "xsio/async/manager.hpp"

//  CONSTRUCTORS  //

XSIO::Async::Manager::Manager() : Manager($::Global::get<Options>()) {}
XSIO::Async::Manager::Manager(const Options *options) {
  m_storage = $::Unique::New<Storage>(options);
  m_watchdog = $::Unique::New<Watchdog>(this);
  m_scheduler = $::Unique::New<Scheduler>(this);
  m_shutdown = $::Unique::New<Shutdown>(m_mutex);
  m_signals = $::Unique::New<$::Signal::Handler>();

  // prepare a defaulted signal handler (just-in-case)
  m_signals->listen($::Signal::Symbolic::INT);
  m_signals->attach([&](const $::Signal::Code &) { exit(EXIT_FAILURE); });

  // declare as currently ready
  m_ready.notify();
}