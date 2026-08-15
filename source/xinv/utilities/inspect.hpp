#ifndef _XINV_UTILITIES_INSPECT_HPP
#define _XINV_UTILITIES_INSPECT_HPP

/// XINV Includes
#include "xinv/forward/core.hpp"

namespace XI {

/// @brief Allows inspection of service traits.
template <class T> struct Inspect : private $::Ensure::Static {
  //  TYPEDEFS  //

  //  PUBLIC METHODS  //

  static inline consteval $::String::View name() noexcept { return $::RTTI::Name<T>(); }
  static inline consteval $::RTTI::Tag hash() noexcept { return $::RTTI::Hash(name()); }

  static inline consteval bool transient() noexcept { return std::derived_from<T, Transient>; }
  static inline consteval bool singleton() noexcept { return std::derived_from<T, Singleton>; }

  /**
   * @brief Handles instantiating services.
   * @param services                Services container.
   * @param args                    Construction arguments.
   */
  template <class... As> static inline constexpr $::Unique::Pointer<T> create(Container *services, As &&...args) {
    if constexpr (m_anonymous<As...>()) return $::Unique::New<T>(std::forward<As>(args)...);
    else return $::Unique::New<T>(services, std::forward<As>(args)...); // using container
  }

private:
  //  PRIVATE METHODS  //

  /// @brief Denotes if a service is anonymously constructible.
  template <class... As> static inline consteval bool m_anonymous() noexcept {
    return !std::constructible_from<T, Container *, As...>;
  }

  //  ASSERTIONS  //

  static_assert(std::derived_from<T, Abstract>, "Service does not extend XI::Abstract");
  static_assert(transient() != singleton(), "Service does not extend a suitable lifetime scope");
};

} // namespace XI

#endif
