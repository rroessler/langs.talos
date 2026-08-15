#ifndef _TALOS_MACHINE_LOGGER_HPP
#define _TALOS_MACHINE_LOGGER_HPP

/// Talos Includes
#include "talos/forward/machine.hpp"

namespace Talos::Machine {

/// @brief Utility Class for Logging.
class Logger {
  //  PROPERTIES  //

  /// @brief Bound compiler instance.
  Compiler *m_compiler;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a logger instance.
   * @param compiler                Compiler instance.
   */
  constexpr Logger(Compiler *compiler = nullptr) : m_compiler(compiler) {}

  //  PUBLIC METHODS  //

  /// @brief Pads header spacing as necessary.
  inline constexpr void spacing() { m_compiler->comment(""); }

  /**
   * @brief Handles emitting inline comments.
   * @param fmt               Message format.
   * @param args              Comment arguments.
   */
  inline constexpr void header(const $::String::View &message) { m_header(message); }
  template <class... As> inline constexpr void header(fmt::format_string<As...> fmt, As &&...args) {
    m_header(fmt::format(fmt, std::forward<As>(args)...));
  }

  /**
   * @brief Handles emitting inline comments.
   * @param fmt               Message format.
   * @param args              Comment arguments.
   */
  inline constexpr void comment(const $::String::View &message) { m_comment(message); }
  template <class... As> inline constexpr void comment(fmt::format_string<As...> fmt, As &&...args) {
    m_comment(fmt::format(fmt, std::forward<As>(args)...));
  }

private:
  //  PRIVATE METHODS  //

  /**
   * @brief Constructs comments as needed.
   * @param message           Message to bind.
   */
  inline constexpr void m_header(const $::String::View &message) {
    auto ignored = "\n; " + $::String::Buffer(message);
    m_compiler->comment(ignored.data()); // and assign
  }

  /**
   * @brief Constructs comments as needed.
   * @param message           Message to bind.
   */
  inline constexpr void m_comment(const $::String::View &message) {
    m_compiler->cc->set_inline_comment(message.data());
  }
};

} // namespace Talos::Machine

#endif
