#ifndef _XTDLIB_SPINNER_ABSTRACT_HPP
#define _XTDLIB_SPINNER_ABSTRACT_HPP

/// Library Includes
#include "xtdlib/spinner/enabled.hpp"
#include "xtdlib/spinner/options.hpp"

/// Forward Declarations
$_FWD($::Spinner, class Abstract)

/// Forward Definitions
$_FWD($::Spinner, using Pointer = Shared::Pointer<Abstract>)

namespace $::Spinner {

/// @brief Spinner Abstraction.
class $_ABSTRACT Abstract : public Shared::Recast<Abstract> {
  //  PROPERTIES  //

  /// @brief The underlying write mutex.
  mutable Mutex::Auto m_mutex;

  /// @brief Forces a display reset.
  bool m_reset = false;

  /// @brief Denotes if the spinner has finished.
  bool m_complete = false;

  /// @brief The current frame index.
  uint32_t m_frame = 0;

  /// @brief The bound options.
  Options m_options = {};

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Handles constructing a spinner.
   * @param options                 Options to use.
   */
  explicit Abstract(const Options &options = {});
  explicit Abstract(const $::String::Buffer &text, Mode mode = Mode::RESOLVE);

  /// @brief Handles dismissing the spinner.
  virtual ~Abstract() { dismiss(); }

  //  PUBLIC METHODS  //

  /// @brief Gets the associated options.
  inline constexpr const Options &options() const { return m_options; }

  /// @brief Allows updating the underlying tick-value.
  inline constexpr const Chrono::Duration &tick() const { return m_options.tick; }
  inline Abstract &tick(const Chrono::Duration &duration) { return m_override(m_options.tick, duration); }

  /// @brief Allows updating the underlying mode.
  inline constexpr Mode mode() const { return m_options.mode; }
  inline constexpr Abstract &mode(Mode next) { return m_options.mode = next, *this; }

  /// @brief Allows updating current prefix text.
  inline constexpr String::View prefix() const { return m_options.prefix; }
  inline Abstract &prefix(const Color::ANSI &text) { return prefix(fmt::to_string(text)); }
  inline Abstract &prefix(const String::Buffer &text) { return m_override(m_options.prefix, text); }

  /// @brief Allows updating current suffix text.
  inline constexpr String::View suffix() const { return m_options.suffix; }
  inline Abstract &suffix(const Color::ANSI &text) { return suffix(fmt::to_string(text)); }
  inline Abstract &suffix(const String::Buffer &text) { return m_override(m_options.suffix, text); }

  /**
   * @brief Forces a refresh of the spinner.
   * @param suffix                  Suffix to use.
   */
  void refresh();
  void refresh(const Color::ANSI &suffix);
  void refresh(const $::String::Buffer &suffix);

  /**
   * @brief Handles dismissing the spinner.
   * @param text                    Dismissal text.
   */
  void dismiss(const $::String::Buffer &text = {});

protected:
  //  PRIVATE METHODS  //

  /// @brief Handles clearing lines as necessary.
  void m_clear();

  /// @brief Handles writing outputs to the display.
  void m_loop();

  /// @brief Handles printing the current details.
  void m_print();

  /// @brief Handles dismissing the spinner instance.
  virtual inline void m_dismiss() {}

  /// @brief Handles checking quit conditions.
  virtual inline bool m_running() const { return !m_complete; }

  /// @brief Handles incoming sleep handling.
  virtual inline void m_sleep() const noexcept { std::this_thread::sleep_for(m_options.tick.underlying()); }

  /**
   * @brief Handles overriding properties.
   * @param property                  Property to write.
   * @param next                      Next value to update.
   */
  template <class T, std::convertible_to<T> U = T> inline Abstract &m_override(T &property, const U &next) {
    $_UNUSED $_AUTO = Lock::guard(m_mutex);
    return m_reset = true, property = next, *this;
  }
};

/// @brief Basic Spinner Implementation.
class Basic : public Abstract {
  //  PROPERTIES  //

  /// @brief Underlying joinable thread.
  std::thread m_thread;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs the thread instance.
   * @param args              Spinner options.
   */
  template <class... As>
  constexpr Basic(As &&...args) : Abstract(std::forward<As>(args)...), m_thread(&Basic::m_loop, this) {}

protected:
  //  PRIVATE METHODS  //

  /// @brief Handles dismissing the internal thread.
  inline void m_dismiss() final { m_thread.join(); }
};

} // namespace $::Spinner

#endif
