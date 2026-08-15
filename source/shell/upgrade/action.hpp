#ifndef _SHELL_UPGRADE_ACTION_HPP
#define _SHELL_UPGRADE_ACTION_HPP

/// Shell Includes
#include "shell/command/abstract.hpp"

namespace Shell::Upgrade {

/// @brief Available Upgrade Options.
struct Options {
  //  PROPERTIES  //

  /// @brief Performs upgrade checks only.
  bool dry = false;

  /// @brief Forcefully upgrades the current executable.
  bool force = false;

  /// @brief Suppresses all diagnostic outputs.
  bool verbose = true;

  /// @brief The tag of the version to install.
  $::String::Buffer tag = "latest";
};

/// @brief Upgrade Command.
class Action : public Command::Abstract {
  //  PROPERTIES  //

  /// @brief Available upgrade options.
  Options m_options = {};

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs a upgrade action.
  explicit Action();

protected:
  //  PRIVATE METHODS  //

  /// @brief Handles uninstalling.
  void m_remove();

  /// @brief Handles executing the upgrader.
  void m_execute();

  /// @brief Gets the current installation directory.
  $::FS::Path m_installation() const;

  /**
   * @brief Handles subscribing the "upgrade" command.
   * @param command                   CLI application.
   */
  void m_subscribe(CLI::App *command) final;
};

} // namespace Shell::Upgrade

#endif
