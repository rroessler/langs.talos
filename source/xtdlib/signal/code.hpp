#ifndef _XTDLIB_SIGNAL_CODE_HPP
#define _XTDLIB_SIGNAL_CODE_HPP

/// Library Includes
#include "xtdlib/string/view.hpp"

//  X-MACROS  //

/// @brief All available symbolic signals.
#define $_XX_SIGNALS_LIST(X)             \
  X(HUP, 1, "Terminal Hung Up")          \
  X(INT, 2, "Keyboard Interrupt")        \
  X(QUIT, 3, "Quit Request")             \
  X(ILL, 4, "Illegal Instruction")       \
  X(TRAP, 5, "Trace of Breakpoint Trap") \
  X(ABRT, 6, "Abort Request")            \
  X(BUS, 7, "Bad Memory Access")         \
  X(FPE, 8, "Floating Point Exception")  \
  X(KILL, 9, "Forced Quit Request")      \
  X(USR1, 10, "User Defined Signal 1")   \
  X(SEGV, 11, "Segmentation Fault")      \
  X(USR2, 12, "User Defined Signal 2")   \
  X(PIPE, 13, "Broken Pipe")             \
  X(ALRM, 14, "Timer Expired")           \
  X(TERM, 15, "Polite Quit Request")

//  NAMESPACES  //

namespace $::Signal {

/// @brief Underlying signal values.
using Underlying = int32_t;

/// @brief The Symbolic Signal Codes.
enum class Symbolic : Underlying { $_XX_SIGNALS_LIST($_XX_ENUM_VALUE) UNK = -1 };

/// @brief For unknown signal values.
static inline constexpr Symbolic Unknown() { return Symbolic::UNK; }

/// @brief Underlying code value.
class Code {
  //  PROPERTIES  //

  /// @brief Underlying code-value.
  Symbolic m_value = Symbolic::UNK;

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs an "OKAY" value.
  explicit constexpr Code() = default;

  /**
   * @brief Constructs a signal instance.
   * @param value                 Value to assign.
   */
  constexpr Code(Symbolic value) : m_value(value) {}

  /**
   * @brief Constructs a signal instance.
   * @param value                 Value to assign.
   */
  constexpr Code(Underlying value) {
    switch (value) {
    case SIGINT: m_value = Symbolic::INT; break;
    case SIGILL: m_value = Symbolic::ILL; break;
    case SIGFPE: m_value = Symbolic::FPE; break;
    case SIGABRT: m_value = Symbolic::ABRT; break;
    case SIGTERM: m_value = Symbolic::TERM; break;
    case SIGSEGV: m_value = Symbolic::SEGV; break;

    // ignore any non-compliant signals
    default: break;
    }
  }

  /**
   * @brief Handles constructing a named signal.
   * @param name                  Name of signal.
   */
  constexpr Code(const String::View &name) : m_value(Unknown()) {
#define X(N, ...)                                            \
  case XH::FNV::U32("SIG" #N): m_value = Symbolic::N; break;
    switch (XH::FNV::U32(name)) { $_XX_SIGNALS_LIST(X) }
#undef X
  }

  //  PUBLIC METHODS  //

  /// @brief Gets the associated name.
  inline constexpr String::View label() const noexcept {
#define X(N, ...)                    \
  case Symbolic::N: return "SIG" #N;
    switch (m_value) { $_XX_SIGNALS_LIST(X) default : return "SIGUNK"; }
#undef X
  }

  /// @brief Gets the underlying code value.
  inline constexpr Symbolic symbolic() const noexcept { return m_value; }

  /// @brief Converts the signal to a suitable error-code.
  inline constexpr Underlying errc() const noexcept { return 128 + static_cast<Underlying>(m_value); }

  /// @brief Gets the underlying numeric value.
  inline constexpr Underlying native() const noexcept {
    switch (m_value) {
    case Symbolic::INT: return SIGINT;
    case Symbolic::ILL: return SIGILL;
    case Symbolic::FPE: return SIGFPE;
    case Symbolic::ABRT: return SIGABRT;
    case Symbolic::TERM: return SIGTERM;
    case Symbolic::SEGV: return SIGSEGV;

    // otherwise default to an unknown value
    default: return -1;
    }
  }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles printing signals.
   * @param os                    Output stream.
   * @param self                  Signal code.
   */
  static inline void m_print(std::ostream &os, const Code &self) { os << self.label(); }
};

} // namespace $::Signal

#endif
