#ifndef _XPC_SHELL_TYPES_HPP
#define _XPC_SHELL_TYPES_HPP

/// XPC Includes
#include "xpc/pipe/direct.hpp"
#include "xpc/shell/path.hpp"

namespace XPC::Shell {

/// @brief Variadic Argument Collection.
using Args = std::vector<$::String::Buffer>;

/// @brief Command Environment Mapping.
using Environ = $::Map::Dict<$::String::Buffer>;

/// @brief Child Command Options.
struct Options {
  //  PROPERTIES  //

  Pipe::Direct cin = Pipe::Direct::INHERIT;  // Standard input redirect.
  Pipe::Direct cout = Pipe::Direct::INHERIT; // Standard output redirect.
  Pipe::Direct cerr = Pipe::Direct::INHERIT; // Standard error redirect.

  /// @brief The arguments to execute (with program at front).
  Args argv = {};

  /// @brief Current working directory to inherit (empty means use current).
  $::String::Buffer cwd = {};

  /// @brief The given environment to inherit.
  Environ envp = $::Environ::view();
};

/// @brief Shell Options Builder.
class Builder {
  //  PROPERTIES  //

  /// @brief The underlying options.
  Options m_options = {};

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Allow pre-defining options.
   * @param options               Options to inherit.
   */
  constexpr Builder(const Options &options = {}) : m_options(options) {}
  constexpr Builder(const $::String::Buffer &command, const Options &options = {}) : Builder(options) {
    m_options.argv.insert(m_options.argv.begin(), command); // emplace the command
  }

  //  PUBLIC METHODS  //

  /// @brief Merges all the options together.
  inline constexpr const Options &merge() const noexcept { return m_options; }

  inline constexpr Pipe::Direct cin() const noexcept { return m_options.cin; }
  inline constexpr Builder &cin(Pipe::Direct redirect) noexcept { return m_options.cin = redirect, *this; }

  inline constexpr Pipe::Direct cout() const noexcept { return m_options.cout; }
  inline constexpr Builder &cout(Pipe::Direct redirect) noexcept { return m_options.cout = redirect, *this; }

  inline constexpr Pipe::Direct cerr() const noexcept { return m_options.cerr; }
  inline constexpr Builder &cerr(Pipe::Direct redirect) noexcept { return m_options.cerr = redirect, *this; }

  inline constexpr $::String::View cwd() const noexcept { return m_options.cwd; }
  inline constexpr Builder &cwd(const $::String::Buffer &cwd) noexcept { return m_options.cwd = cwd, *this; }

  inline constexpr const Args &argv() const noexcept { return m_options.argv; }
  inline constexpr Builder &argv(const Args &argv) noexcept { return $::Ranges::Append(m_options.argv, argv), *this; }

  inline constexpr const Environ &envp() const noexcept { return m_options.envp; }
  inline constexpr Builder &envp(const Environ &envp) noexcept { return m_options.envp = envp, *this; }
  inline constexpr Builder &envp(const $::String::Buffer &key, const $::String::Buffer &value) noexcept {
    return m_options.envp[key] = value, *this;
  }
};

} // namespace XPC::Shell

#endif
