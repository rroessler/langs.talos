#ifndef _TALOS_LOCALE_SERVICE_HPP
#define _TALOS_LOCALE_SERVICE_HPP

/// Talos Includes
#include "talos/locale/options.hpp"

namespace Talos::Locale {

/// @brief Underlying Locale Service.
class Service : public XI::Singleton, public XI::Immediate {
  //  PROPERTIES  //

  /// @brief Underlying options available.
  const Options *m_options;

  /// @brief Keep a copy of the base locale.
  std::locale m_classic = std::locale::classic();

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs a defaulted locale service.
  explicit Service();

  /**
   * @brief Constructs a locale service.
   * @param options               Options to bind.
   */
  explicit Service(const Options *options);

  /**
   * @brief Constructs a locale service.
   * @param services              Services container.
   */
  explicit Service(XI::Container *services);

  //  PUBLIC METHODS  //

  /// @brief Gets the underlying garbage options.
  inline constexpr const Options *options() const noexcept { return m_options; }

  /// @brief Handles resetting the current locale.
  inline void reset() { update(m_classic); }

  /**
   * @brief Handles updating the locale with construction.
   * @tparam As                       Argument types.
   * @param args                      Locale arguments.
   */
  template <class... As> inline void update(As &&...args) {
    const auto &locale = std::locale(std::forward<As>(args)...);
    return update(locale); // and forcibly update from overload
  }

  /**
   * @brief Sets the current global locale.
   * @param locale                    Locale to be bound.
   */
  inline void update(const std::locale &locale) {
    auto color = $::Color::Enabled(std::cout); // get the color enablement
    std::locale::global(std::locale(locale, new $::Color::Facet(color)));
  }
};

} // namespace Talos::Locale

#endif
