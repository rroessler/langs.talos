#ifndef _XINV_UTILITIES_CONTAINER_HPP
#define _XINV_UTILITIES_CONTAINER_HPP

/// XINV Includes
#include "xinv/service/immediate.hpp"
#include "xinv/service/singleton.hpp"
#include "xinv/service/transient.hpp"
#include "xinv/utilities/inspect.hpp"

namespace XI {

/// @brief Services Factory Signature.
template <std::derived_from<Abstract> T> using Factory = $::Unique::Functor<T *(Container *)>;

/// @brief Services Container.
class Container {
  //  PROPERTIES  //

  /// @brief Handles locking service construction.
  mutable $::Mutex::Auto m_mutex;

  /// @brief Bound singleton services available.
  $::Map::Base<$::RTTI::Tag, Factory<Singleton>> m_services = {};

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs an empty services container.
  constexpr Container() = default;

  //  OPERATOR METHODS  //

  /// @brief Allows getting services through de-referencing.
  template <std::derived_from<Singleton> T> inline constexpr operator T *() { return get<T>(); }

  /// @brief Allows creating services through de-referencing.
  template <std::derived_from<Transient> T> inline constexpr operator $::Unique::Pointer<T>() { return m_reify<T>(); }

  //  PUBLIC METHODS  //

  /// @brief Checks if a singleton service is bound to a container.
  template <std::derived_from<Singleton> T> inline constexpr bool exists() const noexcept {
    return m_services.contains($::RTTI::Hash<T>());
  }

  /// @brief Allows getting conditional services safely.
  template <std::derived_from<Singleton> T> inline constexpr T *when() noexcept {
    return exists<T>() ? get<T>() : nullptr;
  }

  /// @brief Attempts getting a shared service instance.
  template <std::derived_from<Singleton> T> inline constexpr T *get() noexcept {
    return static_cast<T *>(m_services.at(m_hash<T, true>())(this));
  }

  /**
   * @brief Handles getting transient services.
   * @param args                Constructor arguments.
   */
  template <std::derived_from<Transient> T, class... As> inline constexpr $::Unique::Pointer<T> get(As &&...args) {
    return m_reify<T>(std::forward<As>(args)...);
  }

  /**
   * @brief Binds singleton service factories.
   * @param args                Constructor arguments.
   */
  template <std::derived_from<Singleton> T, class... As> inline constexpr void bind(As &&...args) {
    $_UNUSED $_AUTO = $::Lock::guard(m_mutex);
    static constexpr auto s_hash = $::RTTI::Hash<T>();
    auto factory = m_bind<T, Singleton>(std::forward<As>(args)...);
    m_services.try_emplace(m_hash<T, false>(), std::move(factory));
    if constexpr (std::derived_from<T, Immediate>) m_services.at(s_hash)(this);
  }

  /**
   * @brief Creates transient service factories.
   * @param args                Constructor arguments.
   */
  template <std::derived_from<Transient> T, class... As> inline constexpr Factory<T> bind(As &&...args) {
    return m_bind(std::forward<As>(args)...);
  }

  /**
   * @brief Handles loading immediate services.
   * @param args                Constructor arguments.
   */
  template <std::derived_from<Singleton> T, class... As> inline constexpr T *load(As &&...args) {
    static constexpr auto s_name = $::RTTI::Name<std::remove_cvref_t<T>>();
    static constexpr auto s_hash = $::RTTI::Hash(s_name); // and the hash
    if (!m_services.contains(s_hash)) bind<T>(std::forward<As>(args)...);
    else $_WARN("XI::Container / Already instantiated service '{}'", s_name);
    return static_cast<T *>(m_services.at(s_hash)(this)); // fast-resolve now
  }

private:
  //  PRIVATE METHODS  //

  /// @brief Gets a pre-validated hash for a service.
  template <class T, bool E> inline constexpr $::RTTI::Tag m_hash() const {
    $_UNUSED static constexpr auto s_name = $::RTTI::Name<std::remove_cvref_t<T>>();
    $_UNUSED static constexpr auto s_state = E ? "not" : "already";
    $_UNUSED static constexpr auto s_msg = "XI::Container service {0} bound '{1}'";
    static constexpr auto s_hash = $::RTTI::Hash(s_name); // get the incoming hash
    return $_ASSERT(m_services.contains(s_hash) == E, s_msg, s_state, s_name), s_hash;
  }

  /**
   * @brief Handles constructing service instances.
   * @param args                Construction arguments.
   */
  template <std::derived_from<Abstract> T, class... As> inline $::Unique::Pointer<T> m_reify(As &&...args) {
    return Inspect<T>::create(this, std::forward<As>(args)...);
  }

  /**
   * @brief Handles constructing service factories.
   * @param args                Construction arguments.
   */
  template <std::derived_from<Abstract> T, std::derived_from<Abstract> R = T, class... As>
  inline constexpr Factory<R> m_bind(As &&...args) const noexcept {
    return [... args = std::forward<As>(args)](Container *self) mutable {
      static auto s_service = self->m_reify<T>(std::forward<As>(args)...);
      if constexpr (std::same_as<T, R>) return s_service.get();
      else return static_cast<R *>(s_service.get()); // resolved
    };
  }
};

} // namespace XI

#endif
