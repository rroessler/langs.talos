/// XPC Includes
#include "xpc/process/child.hpp"
#include "xpc/shell/guard.hpp"
#include "xpc/shell/path.hpp"

#if $_PLATFORM_WINDOWS

/// Platform Includes
#include <TlHelp32.h>

//  PRIVATE METHODS  //

void XPC::Process::Child::m_initialize(const $::String::Buffer &program, const Shell::Options &options) {
  // prepare the incoming startup information
  STARTUPINFOA startup = {};

  startup.cb = sizeof(STARTUPINFOA);
  startup.dwFlags = STARTF_USESTDHANDLES;
  startup.hStdInput = ::GetStdHandle(STD_INPUT_HANDLE);
  startup.hStdOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
  startup.hStdError = ::GetStdHandle(STD_ERROR_HANDLE);

  // prepare the input pipe to be used now
  if (options.cin == Pipe::Direct::IGNORE) {
    m_stdin = Pipe::Duplex(Pipe::Atomic::INHERIT);
    startup.hStdInput = m_stdin.input()->handle();
    m_stdin.output()->atomic(false), m_stdin.detach();
  } else if (options.cin == Pipe::Direct::PIPED) {
    m_stdin = Pipe::Duplex(Pipe::Atomic::INHERIT);
    startup.hStdInput = m_stdin.input()->handle();
    m_stdin.output()->atomic(false); // no-detach
  }

  // prepare the standard output pipe now
  if (options.cout == Pipe::Direct::IGNORE) {
    m_stdout = Pipe::Duplex(Pipe::Atomic::INHERIT);
    startup.hStdOutput = m_stdout.output()->handle();
    m_stdout.input()->atomic(false), m_stdout.detach();
  } else if (options.cout == Pipe::Direct::PIPED) {
    m_stdout = Pipe::Duplex(Pipe::Atomic::INHERIT);
    startup.hStdOutput = m_stdout.output()->handle();
    m_stdout.input()->atomic(false); // no-detach
  }

  // prepare the standout error pipe now
  if (options.cerr == Pipe::Direct::IGNORE) {
    m_stderr = Pipe::Duplex(Pipe::Atomic::INHERIT);
    startup.hStdError = m_stderr.output()->handle();
    m_stderr.input()->atomic(false), m_stderr.detach();
  } else if (options.cerr == Pipe::Direct::PIPED) {
    m_stderr = Pipe::Duplex(Pipe::Atomic::INHERIT);
    startup.hStdError = m_stderr.output()->handle();
    m_stderr.input()->atomic(false); // no-detach
  }

  // update the incoming standard error -> standard output (as requires stderr first)
  if (options.cerr == Pipe::Direct::STDOUT) startup.hStdError = startup.hStdOutput;
  if (options.cout == Pipe::Direct::STDERR) startup.hStdOutput = startup.hStdError;

  // rebuild the arguments and environment now
  auto envp = std::vector<char>();
  auto argv = fmt::format("{0}", fmt::join(options.argv, " "));

  // iterate over the incoming process environment now
  for (const auto &[key, value] : options.envp) {
    $::Ranges::Append(envp, key), envp.push_back('=');
    $::Ranges::Append(envp, value), envp.push_back('\0');
  }

  // ensure we cap-off the final value of the environment as well
  envp.push_back('\0');

  // prepare the current-working directory
  auto cwd = options.cwd.empty() ? nullptr : options.cwd.c_str();

  // prepare the process flags to be used
  DWORD flags = 0; // CREATE_UNICODE_ENVIRONMENT;

  // attempt spawning our instance now
  auto success = ::CreateProcessA(
      static_cast<LPCSTR>(program.c_str()),
      static_cast<LPSTR>(argv.data()),
      NULL,
      NULL,
      true,
      flags,
      static_cast<LPVOID>(envp.data()),
      cwd,
      &startup,
      &m_info
  );

  // fail if we did not receive a suitable success here
  $_EXPECT(success, "Could not execute ::CreateProcessA");

  // set the current process identifier
  m_pid = m_info.dwProcessId;

  // attempt closing the necessary handles
  if (!m_stdin.mirrored()) m_stdin.input()->close();
  if (!m_stdout.mirrored()) m_stdout.output()->close();
  if (!m_stderr.mirrored()) m_stderr.output()->close();
}

bool XPC::Process::Child::m_poll() {
  // check if we have exited correctly already
  if (m_errc != INT32_MIN) return true;

  // prepare the incoming exit-code to resolve
  DWORD errc = 0;

  // check if the child has exited or not
  if (!::GetExitCodeProcess(m_info.hProcess, &errc)) return false;

  // resolve the incoming exit details now
  return errc == STILL_ACTIVE ? false : m_errc = errc;
}

int32_t XPC::Process::Child::m_wait() {
  // check if we have exited correctly already
  if (m_errc != INT32_MIN) return m_errc;

  // attempt waiting for the process to finish now
  auto result = ::WaitForSingleObject(m_info.hProcess, INFINITE);

  // force an error if it timed out or otherwise
  if (result == WAIT_TIMEOUT) return INT32_MIN;
  else if (result == WAIT_ABANDONED) return INT32_MIN;
  else if (result == WAIT_FAILED) return INT32_MIN;

  // attempt getting the resulting exit-code
  DWORD errc = 0;

  // should be able to poll for the exit-code now
  return ::GetExitCodeProcess(m_info.hProcess, &errc) ? m_errc = errc : INT32_MIN;
}

XPC::Process::Identifier XPC::Process::Child::m_ppid() const {
  // ignore if the pid is invalid
  DWORD pid = m_pid.value();
  if (pid == 0) return 0;

  // prepare the process entry details
  PROCESSENTRY32 pe = {};
  pe.dwSize = sizeof(PROCESSENTRY32);

  // prepare the helper snapshot
  HANDLE snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

  // attempt scanning for the value process now
  while (::Process32First(snapshot, &pe)) {
    if (pe.th32ProcessID == pid) return pe.th32ParentProcessID;
  }

  /// return an invalid process identifier if any failures occur
  return 0;
}

bool XPC::Process::Child::m_signal(const $::Signal::Code &signal) {
  // ignore if the result failed at all
  if (m_errc != INT32_MIN) return false;

  // convert the pid as necessary
  auto pid = static_cast<DWORD>(m_pid.value());

  // handle based on the outgoing signal to be sent
  switch (signal.symbolic()) {
  case Signal::KILL: return ::TerminateProcess(&m_info.hProcess, 137);
  case Signal::INT: return ::GenerateConsoleCtrlEvent(CTRL_C_EVENT, pid);
  default: return ::GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, pid);
  }
}

#endif
