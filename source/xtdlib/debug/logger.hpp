#ifndef _XTDLIB_DEBUG_LOGGER_HPP
#define _XTDLIB_DEBUG_LOGGER_HPP

/// Vendor Modules
#include <xhash/xhash.hpp>

/// Library Modules
#include "xtdlib/enum/class.hpp"
#include "xtdlib/macros/processor.hpp"
#include "xtdlib/string/view.hpp"
#include "xtdlib/vendors/fmt.hpp"
#include "xtdlib/vendors/spdlog.hpp"

//  X-MACROS  //

/// Available logger levels.
#define XX_LOGGER_LEVELS(X) \
    X(TRACE, trace, trace)  \
    X(DEBUG, debug, debug)  \
    X(WARN, warn, warn)     \
    X(ERROR, error, err)    \
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
    $_XX_ENUM_CLASS(Level, uint8_t, XX_LOGGER_LEVELS, OFF, DEFAULT = $_PP_NDEBUG ? WARN : DEBUG);

}  // namespace $::Logger

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

    /**
     * @brief Handles updating the logger-color.
     * @param level                 Color to update.
     */
    void update(Color color);

    /**
     * @brief Handles updating the logger-level.
     * @param level                 Level to update.
     */
    static inline spdlog::level::level_enum resolve(Level level) {
#define X(N, _, L) \
    case Level::N: return spdlog::level::level_enum::L;
        switch (level) { XX_LOGGER_LEVELS(X) default : break; }
        return spdlog::level::level_enum::off;  // "off" as default
#undef X
    }

    /**
     * @brief Handles updating the logger-level.
     * @param level                 Level to update.
     */
    static inline Level resolve(spdlog::level::level_enum level) {
#define X(N, _, L) \
    case spdlog::level::level_enum::L: return Level::N;
        switch (level) { XX_LOGGER_LEVELS(X) default : break; }
        return Level::OFF;  // "off" as default to be returned
#undef X
    }

    /**
     * @brief Handles updating the logger-level.
     * @param level                 Level to update.
     */
    static inline Level resolve(const String::View& level) {
#define X(N, L, ...) \
    case XH::FNV::U32(#L): return Level::N;
        switch (XH::FNV::U32(level)) { XX_LOGGER_LEVELS(X) default : break; }
        return Level::DEFAULT;  // should result to default here
#undef X
    }

    /**
     * @brief Handles updating the logger-color.
     * @param level                 Color to update.
     */
    static inline spdlog::color_mode resolve(Color color) {
        switch (color) {
            case Color::ALWAYS: return spdlog::color_mode::always;
            case Color::AUTO: return spdlog::color_mode::automatic;
            default: return spdlog::color_mode::never;  // default
        }
    }

}  // namespace $::Logger::Options

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
    void write(Level level, const String::View& message);

    /**
     * @brief Handles writing individual values.
     * @param level                 Logger level.
     * @param value                 Value to write.
     */
    template <class T>
    static inline void write(Level level, const T& value) {
        write(level, String::View(fmt::to_string(value)));
    }

    /**
     * @brief Handles writing formatted messages.
     * @param level                 Logger level.
     * @param message               Message to write.
     * @param args                  Arguments to format.
     */
    template <class... As>
    static inline void write(Level level, fmt::format_string<As...> message, As&&... args) {
        write(level, fmt::format(message, std::forward<As>(args)...));
    }

#define X(N, F, ...)                                                        \
    template <class T>                                                      \
    static inline void F(const T& value) {                                  \
        write(Level::N, value);                                             \
    }                                                                       \
                                                                            \
    template <class... As>                                                  \
    static inline void F(fmt::format_string<As...> message, As&&... args) { \
        write(Level::N, message, std::forward<As>(args)...);                \
    }

    XX_LOGGER_LEVELS(X)
#undef X

}  // namespace $::Logger::Output

//  UNDEFINES  //

#undef XX_LOGGER_LEVELS

#endif
