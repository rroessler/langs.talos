#ifndef _SHELL_COMMAND_MACROS_HPP
#define _SHELL_COMMAND_MACROS_HPP

//  X-MACROS  //

/// @brief Common Command Options.
#define SHELL_XX_OPTIONS_COMMON(X) X("-h, --help", "Display this command help menu")

/// @brief Common Bundle Options.
#define SHELL_XX_OPTIONS_BUNDLE(X)                               \
  X("--env", "Set environment file to inherit")                  \
  X("--lint", "Force extra linting to occur")                    \
  X("--hints", "Allows showing extra linting hints")             \
  X("", "")                                                      \
  X("--typeless", "Disables all available type-checking")        \
  X("--optless", "Disables all runtime optimization techniques")

/// @brief Common Launch Options.
#define SHELL_XX_OPTIONS_LAUNCH(X)                                   \
  SHELL_XX_OPTIONS_BUNDLE(X)                                         \
  X("--jitless", "Disables runtime allocation of executable memory")

#endif
