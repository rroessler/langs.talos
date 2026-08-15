/// Library Includes
#include "xtdlib/debug/logger.hpp"
#include "xtdlib/color/enabled.hpp"
#include "xtdlib/macros/forward.hpp"
#include "xtdlib/pointer/shared.hpp"
#include "xtdlib/utility/singleton.hpp"
#include "xtdlib/vendors/spdlog.hpp"

/// Forward Declarations
$_FWD($::Logger, class Global)
$_FWD($::Logger::Options, Level resolve(const String::View &))
$_FWD($::Logger::Options, Level resolve(spdlog::level::level_enum))
$_FWD($::Logger::Options, spdlog::level::level_enum resolve(Level))
$_FWD($::Logger::Options, spdlog::color_mode resolve(Color))

//  TYPEDEFS  //

class $::Logger::Global : public $::Ensure::Singleton<Global> {
  //  TYPEDEFS  //

#if $_PLATFORM_WINDOWS
  /// @brief Specialized sink-typing for Win32.
  struct Sink : public spdlog::sinks::stderr_color_sink_mt {
    using spdlog::sinks::stderr_color_sink_mt::stderr_color_sink_mt;
    inline constexpr bool should_color() const noexcept { return should_do_colors_; }
  };
#else
  /// @brief Underlying sink-typing.
  using Sink = spdlog::sinks::stderr_color_sink_mt;
#endif

  //  PROPERTIES  //

  Sink *m_sink = nullptr;                             // Reference sink value.
  Shared::Pointer<spdlog::logger> m_logger = nullptr; // Bound logger instance.

public:
  //  CONSTRUCTORS  //

  /// @brief Default logger constructor.
  explicit Global() {
    // ensure the logger has been constructed now
    m_logger = spdlog::synchronous_factory::create<Sink>("xtdlib/logger");
    m_sink = dynamic_cast<Sink *>(m_logger->sinks().at(0).get());

    // set the pattern for the sink to be used
    m_sink->set_pattern("%^%l%$ (%P) [%Y-%m-%dT%T.%f%zZ] %v");

    // configure the logger instance now
    m_level(Level::DEFAULT), m_color($::Color::Enabled() ? Color::DEFAULT : Color::NEVER);
  }

  //  PUBLIC METHODS  //

  /// @brief Handles writing values.
  static inline void write(Level level, const String::View &view) { s_instance()->m_write(level, view); }

  /// @brief Gets/sets the current logging level.
  static inline constexpr Level level() { return s_instance()->m_level(); }
  static inline constexpr void level(Level level) { s_instance()->m_level(level); }

  /// @brief Gets/sets the current color mode.
  static inline Color color() { return s_instance()->m_color(); }
  static inline void color(Color color) { s_instance()->m_color(color); }

private:
  //  PRIVATE METHODS  //

  /// @brief Gets the current logging level.
  inline constexpr Level m_level() const { return Options::resolve(m_logger->level()); }

  /**
   * @brief Handles setting the logging level.
   * @param level                     Level to bind.
   */
  inline constexpr void m_level(Level level) {
    auto resolved = Options::resolve(level);
    m_logger->set_level(resolved);
    m_logger->flush_on(resolved);
  }

  /// @brief Gets the current color mode.
  inline constexpr Color m_color() const { return m_sink->should_color() ? Color::ALWAYS : Color::NEVER; }

  /**
   * @brief Sets the current color-mode.
   * @param color                     Color to bind.
   */
  inline constexpr void m_color(Color color) { m_sink->set_color_mode(Options::resolve(color)); }

  /**
   * @brief Handles writing values.
   * @param level                     Logging level.
   * @param view                      Value to write.
   */
  inline void m_write(Level level, const String::View &view) { m_logger->log(Options::resolve(level), view); }
};

//  PUBLIC METHODS  //

$::Logger::Level $::Logger::Options::level() { return Global::level(); }
$::Logger::Color $::Logger::Options::color() { return Global::color(); }

void $::Logger::Options::update(Color color) { Global::color(color); }
void $::Logger::Options::update(Level level) { Global::level(level); }
void $::Logger::Options::update(const $::String::View &level) { update(resolve(level)); }

void $::Logger::Output::write(Level level, const String::View &view) { Global::write(level, view); }

spdlog::level::level_enum $::Logger::Options::resolve(Level level) {
#define X(N, _, L)                                    \
  case Level::N: return spdlog::level::level_enum::L;
  switch (level) { $_XX_LOGGER_LEVELS(X) default : return spdlog::level::level_enum::off; }
#undef X
}

$::Logger::Level $::Logger::Options::resolve(spdlog::level::level_enum level) {
#define X(N, _, L)                                    \
  case spdlog::level::level_enum::L: return Level::N;
  switch (level) { $_XX_LOGGER_LEVELS(X) default : return Level::OFF; }
#undef X
}

$::Logger::Level $::Logger::Options::resolve(const String::View &level) {
#define X(N, L, ...)                      \
  case XH::FNV::U32(#N): $_FALLTHROUGH;   \
  case XH::FNV::U32(#L): return Level::N;
  switch (XH::FNV::U32(level)) { $_XX_LOGGER_LEVELS(X) default : return Level::DEFAULT; }
#undef X
}

spdlog::color_mode $::Logger::Options::resolve(Color color) {
  switch (color) {
  case Color::ALWAYS: return spdlog::color_mode::always;
  case Color::AUTO: return spdlog::color_mode::automatic;
  default: return spdlog::color_mode::never; // default
  }
}
