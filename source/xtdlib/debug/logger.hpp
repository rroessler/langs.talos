#ifndef _XTDLIB_DEBUG_LOGGER_HPP
#define _XTDLIB_DEBUG_LOGGER_HPP

/// Vendor Includes
#include <xhash/xhash.hpp>

/// Library Includes
#include "xtdlib/debug/printable.hpp"
#include "xtdlib/enum/class.hpp"
#include "xtdlib/macros/processor.hpp"
#include "xtdlib/string/view.hpp"
#include "xtdlib/vendors/fmt.hpp"

//  X-MACROS  //

/// Available logger levels.
#define $_XX_LOGGER_LEVELS(X) \
  X(TRACE, trace, trace)      \
  X(DEBUG, debug, debug)      \
  X(WARN, warn, warn)         \
  X(ERROR, error, err)        \
  X(FATAL, fatal, critical)

//  MACROS  //

#define $_TRACE(...) ::$::Logger::Output::trace(__VA_ARGS__)
#define $_DEBUG(...) ::$::Logger::Output::debug(__VA_ARGS__)
#define $_WARN(...) ::$::Logger::Output::warn(__VA_ARGS__)
#define $_ERROR(...) ::$::Logger::Output::error(__VA_ARGS__)
#define $_FATAL(...) ::$::Logger::Output::fatal(__VA_ARGS__)

//  NAMESPACES  //

namespace $::Logger {

//  TYPEDEFS  //

/// @brief Color mode to be used.
enum class Color : uint8_t { NEVER, ALWAYS, AUTO, DEFAULT = AUTO };

/// @brief Available logger levels.
$_XX_ENUM_CLASS(Level, uint8_t, $_XX_LOGGER_LEVELS, OFF, DEFAULT = $_PP_NDEBUG ? WARN : DEBUG);

} // namespace $::Logger

namespace $::Logger::Options {

//  PUBLIC METHODS  //

/// @brief Gets the current logging level.
Level level();

/// @brief Gets the current logging color.
Color color();

/**
 * @brief Handles updating the logger-level.
 * @param level                 Level to update.
 */
void update(Level level);
void update(const $::String::View &level);

/**
 * @brief Handles updating the logger-color.
 * @param level                 Color to update.
 */
void update(Color color);

} // namespace $::Logger::Options

namespace $::Logger::Output {

/// @brief Handles forcing the logger to be stopped.
static inline void stop() { Options::update(Level::OFF); }

/// @brief Handles forcing the logger to be started.
static inline void start(Level level = Level::DEFAULT) {
  if (Options::level() == Level::OFF) Options::update(level);
}

/**
 * @brief Handles writing outputs to the logger.
 * @param level                 Logger level.
 * @param message               Message to write.
 */
void write(Level level, const String::View &message);

/**
 * @brief Handles writing individual values.
 * @param level                 Logger level.
 * @param value                 Value to write.
 */
template <class T> static inline void write(Level level, const T &value) {
  write(level, String::View(fmt::to_string(value)));
}

/**
 * @brief Handles writing formatted messages.
 * @param level                 Logger level.
 * @param message               Message to write.
 * @param args                  Arguments to format.
 */
template <class... As> static inline void write(Level level, fmt::format_string<As...> message, As &&...args) {
  write(level, fmt::format(message, std::forward<As>(args)...));
}

#define X(N, F, ...)                                                                             \
  template <class T> static inline void F(const T &value) { write(Level::N, value); }            \
  template <class... As> static inline void F(fmt::format_string<As...> message, As &&...args) { \
    write(Level::N, message, std::forward<As>(args)...);                                         \
  }

$_XX_LOGGER_LEVELS(X)
#undef X

} // namespace $::Logger::Output

//  UNDEFINES  //

#undef XX_LOGGER_LEVELS

#endif
