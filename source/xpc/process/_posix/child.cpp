/// XPC Includes
#include "xpc/process/child.hpp"
#include "xpc/shell/guard.hpp"
#include "xpc/shell/path.hpp"

#if $_PLATFORM_POSIX

/// C++ Modules
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <stdexcept>

#if $_PLATFORM_DARWIN
#include <sys/sysctl.h>
#endif

/// System Includes
#include <spawn.h>
#include <sys/wait.h>

/// Forward Definitions
$_FWD(XPC::Process, class Actions)
$_FWD(XPC::Process, class Attributes)

//  MACROS  //

#define MM_POSIX_SPAWN(FN, ...)                                                                       \
  auto errc = ::FN(__VA_ARGS__);                                                                      \
  if (errc != 0) throw std::runtime_error($::String::Buffer(#FN) + " failed: " + std::strerror(errc))

//  TYPEDEFS  //

class XPC::Process::Actions {
  //  PROPERTIES  //

  /// @brief Underlying posix-spawn actions.
  posix_spawn_file_actions_t m_actions = {};

public:
  //  CONSTRUCTORS  //

  /// @brief Handles constructing actions.
  constexpr Actions() { MM_POSIX_SPAWN(posix_spawn_file_actions_init, &m_actions); }

  /// @brief Handles destructing actions.
  constexpr ~Actions() noexcept(false) { MM_POSIX_SPAWN(posix_spawn_file_actions_destroy, &m_actions); }

  //  PUBLIC METHODS  //

  /// @brief Gets the underlying actions.
  inline constexpr posix_spawn_file_actions_t *get() noexcept { return &m_actions; }

  /// @brief Adds a close action.
  inline constexpr void close(Pipe::Handle handle) {
    MM_POSIX_SPAWN(posix_spawn_file_actions_addclose, &m_actions, handle);
  }

  /// @brief Adds a dup2 action.
  inline constexpr void dupe(Pipe::Handle handle, Pipe::Handle next) {
    MM_POSIX_SPAWN(posix_spawn_file_actions_adddup2, &m_actions, handle, next);
  }
};

class XPC::Process::Attributes {
  //  PROPERTIES  //

  /// @brief Underlying signals mask.
  sigset_t m_mask = {};

  /// @brief The bound attributes available.
  posix_spawnattr_t m_attributes = {};

public:
  //  CONSTRUCTORS  //

  /// @brief Handles constructing attributes.
  constexpr Attributes() {
    MM_POSIX_SPAWN(posix_spawnattr_init, &m_attributes);
    sigemptyset(&m_mask), signals(&m_mask); // prepare
  }

  /// @brief Handles destructing attributes.
  constexpr ~Attributes() noexcept(false) { MM_POSIX_SPAWN(posix_spawnattr_destroy, &m_attributes); }

  //  PUBLIC METHODS  //

  inline constexpr posix_spawnattr_t *get() noexcept { return &m_attributes; }
  inline constexpr void set(short flags) { MM_POSIX_SPAWN(posix_spawnattr_setflags, &m_attributes, flags); }
  inline constexpr void signals(sigset_t *mask) {
    set(POSIX_SPAWN_SETSIGMASK); // declare we are using a sigmask
    MM_POSIX_SPAWN(posix_spawnattr_setsigmask, &m_attributes, mask);
  }
};

//  PRIVATE METHODS  //

void XPC::Process::Child::m_initialize(const $::String::Buffer &program, const Shell::Options &options) {
  // prepare the file-actions and attributes to be inherited
  auto actions = Actions();
  auto attributes = Attributes();

  // prepare the input pipe to be used now
  if (options.cin == Pipe::Direct::IGNORE) actions.close(STDIN_FILENO);
  else if (options.cin == Pipe::Direct::PIPED) {
    m_stdin = Pipe::Duplex(Pipe::Atomic::INHERIT);
    actions.close(m_stdin.output()->handle());
    actions.dupe(m_stdin.input()->handle(), STDIN_FILENO);
    actions.close(m_stdin.input()->handle());
    m_stdin.output()->atomic(false);
  }

  // prepare the standard output pipe now
  if (options.cout == Pipe::Direct::IGNORE) actions.close(STDOUT_FILENO);
  else if (options.cout == Pipe::Direct::PIPED) {
    m_stdout = Pipe::Duplex(Pipe::Atomic::INHERIT);
    actions.close(m_stdout.input()->handle());
    actions.dupe(m_stdout.output()->handle(), STDOUT_FILENO);
    actions.close(m_stdout.output()->handle());
    m_stdout.input()->atomic(false);
  }

  // prepare the standout error pipe now
  if (options.cerr == Pipe::Direct::IGNORE) actions.close(STDERR_FILENO);
  else if (options.cerr == Pipe::Direct::STDOUT) actions.dupe(STDOUT_FILENO, STDERR_FILENO);
  else if (options.cerr == Pipe::Direct::PIPED) {
    m_stderr = Pipe::Duplex(Pipe::Atomic::INHERIT);
    actions.close(m_stderr.input()->handle());
    actions.dupe(m_stderr.output()->handle(), STDERR_FILENO);
    actions.close(m_stderr.output()->handle());
    m_stderr.input()->atomic(false);
  }

  // update the incoming standard error -> standard output (as requires stderr first)
  if (options.cout == Pipe::Direct::STDERR) actions.dupe(STDERR_FILENO, STDOUT_FILENO);

  // rebuild the arguments and environment now
  auto argv = std::vector<char *>();
  auto envp = std::vector<char *>();

  // prepare their respective sizes firstly
  argv.reserve(options.argv.size() + 1);
  envp.reserve(options.envp.size() + 1);

  // push any leading values now
  argv.push_back(::strdup(program.c_str()));

  // start by iterating over the available arguments
  for (size_t ii = 1; ii < options.argv.size(); ++ii) argv.push_back(::strdup(options.argv[ii].c_str()));

  // then attempt constructing all the environment values now
  for (const auto &[kk, vv] : options.envp) envp.push_back(::strdup((kk + "=" + vv).c_str()));

  // push the sentinel values now
  argv.push_back(nullptr), envp.push_back(nullptr);

  // attempt spawning our instance now
  $_PP_SCOPE() {
    // we could possible use better system than this mutex
    static $::Mutex::Auto mutex;

    // prepare the output for the pid-value
    pid_t pid = 0;

    // lock the mutex and the current working directory
    $_UNUSED $_AUTO = $::Lock::scope(mutex);
    $_UNUSED $_AUTO = Shell::Guard(options.cwd);

    // actually attempt spawning the process now
    MM_POSIX_SPAWN(posix_spawn, &pid, argv[0], actions.get(), attributes.get(), argv.data(), envp.data());

    // update the resulting pid value now
    m_pid = pid;
  }

  // attempt closing the necessary handles
  if (!m_stdin.mirrored()) m_stdin.input()->close();
  if (!m_stdout.mirrored()) m_stdout.output()->close();
  if (!m_stderr.mirrored()) m_stderr.output()->close();

  // finally clean all the argument and environment values
  for (const auto &arg : $::Ranges::Filter(argv)) ::free(arg);
  for (const auto &kvp : $::Ranges::Filter(envp)) ::free(kvp);
}

bool XPC::Process::Child::m_poll() {
  // check if we have exited correctly already
  if (m_errc != INT32_MIN) return true;

  // check if the child has exited or not (less/equal zero)
  if (::waitpid(m_pid, &m_errc, WNOHANG) < 1) return false;

  // handle updating the exit-status as necessary
  if (WIFEXITED(m_errc)) m_errc = WEXITSTATUS(m_errc);
  else if (!WIFSIGNALED(m_errc)) m_errc = 1;
  else m_errc = -WTERMSIG(m_errc);

  // declare as successfully exited now
  return true;
}

int32_t XPC::Process::Child::m_wait() {
  // check if we have exited correctly already
  if (m_errc != INT32_MIN) return m_errc;

  // attempt waiting for the process to exit
  for (pid_t child = -1;;) {
    child = ::waitpid(m_pid.value(), &m_errc, 0);
    if (child > -1 || errno != EINTR) break;
  }

  // check for a suitable error-code now
  if (WIFEXITED(m_errc)) m_errc = WEXITSTATUS(m_errc);
  else if (!WIFSIGNALED(m_errc)) m_errc = 1;
  else m_errc = -WTERMSIG(m_errc);

  // and return the exit-code
  return m_errc;
}

XPC::Process::Identifier XPC::Process::Child::m_ppid() const {
#if $_PLATFORM_LINUX
  // prepare the maximum buffer size
  static constexpr auto MAXBUF = BUFSIZ * 2;

  // prepare the output process identifier
  int ppid;

  char buffer[MAXBUF]; // prepare the output buffer now
  char procname[32];   // Holds /proc/4294967296/status\0

  // attempt getting the process name here
  ::snprintf(procname, sizeof(procname), "/proc/%ld/status", m_pid.value());

  auto *fp = ::fopen(procname, "r"); // prepare the file
  $_UNUSED $_AUTO = $::Lambda::Defer([fp] { ::fclose(fp); });

  // attempt reading the incoming file now
  if (fp != nullptr) {
    size_t bytes = ::fread(buffer, sizeof(char), MAXBUF - 1, fp);
    if (bytes) buffer[bytes++] = '\0'; // terminate it now
    else return 0;                     // failed to find
  }

  // find end of needle in haystack now
  char *pointer = ::strstr(buffer, "\nPPid:");
  if (pointer == nullptr) return 0; // missing

  // actually attempt scanning for the result now
  int result = ::sscanf(pointer, "\nPPid:%d", &ppid);
  return !result || result == EOF ? 0 : ppid;

#else
  // prepare the incoming process information now
  struct kinfo_proc process_info;
  size_t size = sizeof(struct kinfo_proc);
  int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PID, m_pid};

  if (::sysctl(mib, 4, &process_info, &size, NULL, 0) < 0) return 0;
  if (size == 0) return 0; // failed to find a valid result (maybe)

#if $_PLATFORM_DARWIN
  return process_info.kp_eproc.e_ppid;
#elif defined(__FreeBSD__)
  return process_info.ki_ppid;
#else
#error "Cannot get 'ppid' for this platform"
#endif
#endif
}

bool XPC::Process::Child::m_signal(const $::Signal::Code &signal) {
  return m_errc == INT32_MIN && ::kill(m_pid, signal.native()) == 0;
}

#endif
