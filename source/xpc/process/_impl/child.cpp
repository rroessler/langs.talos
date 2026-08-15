/// XPC Includes
#include "xpc/process/child.hpp"

//  PRIVATE METHODS  //

void XPC::Process::Child::m_initialize(const Shell::Options &options) {
  // ensure there is a valid set of options actually given
  if (options.argv.empty()) throw std::invalid_argument("command arguments cannot be empty");

  // prepare the incoming path variable to be used
  auto iter = options.envp.find("PATH"), cend = options.envp.cend();
  auto path = iter == cend ? std::nullopt : std::optional(iter->second);

  // attempt finding the program now from our
  auto program = Shell::Path::resolve(options.argv[0], path);
  if (program.has_value()) m_initialize(*program, options);
  else throw std::invalid_argument("unknown command " + options.argv[0]);
}

void XPC::Process::Child::m_destroy() {
  // ensure we do not have any zombie processes
  if (m_pid) {
    // we should always wait for closure
    m_wait();

#if $_PLATFORM_WINDOWS // ensure closed
    ::CloseHandle(m_info.hProcess);
    ::CloseHandle(m_info.hThread);
#endif
  }

  // clear the process identifier and error code now
  m_pid = 0, m_errc = INT32_MIN;
}

int32_t XPC::Process::Child::m_wait(const $::Chrono::Duration &duration) {
  return m_wait($::Chrono::Point() + duration);
}

int32_t XPC::Process::Child::m_wait(const $::Chrono::Point &timestamp) {
  // attempt polling whilst possible to do so
  while (timestamp < $::Chrono::Point()) {
    if (poll()) return m_errc; // exit
    std::this_thread::sleep_for(10us);
  }

  // declare a failure here
  return INT32_MIN;
}
