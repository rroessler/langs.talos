#ifndef _XTEST_SESSION_STORAGE_HPP
#define _XTEST_SESSION_STORAGE_HPP

/// Testing Includes
#include "xtest/bench/mark.hpp"
#include "xtest/handle/case.hpp"
#include "xtest/handle/group.hpp"

namespace XT::Session {

/// @brief Storage Container for Tests.
class Storage {
  //  TYPEDEFS  //

  /// @brief Aliased Location Details.
  using Details = Trivia::Location;

  //  PROPERTIES  //

  /// @brief Currently scoped group target.
  Handle::Group *m_target = nullptr;

  /// @brief Available testing suite sections.
  $::Map::Dict<Handle::Group *> m_sections = {};

  /// @brief Currently constructed handles.
  std::vector<$::Unique::Pointer<Handle::Base>> m_handles = {};

public:
  //  CONSTRUCTORS  //

  /// @brief Virtual abstract destructor.
  virtual ~Storage() = default;

  //  PUBLIC METHODS  //

  /// @brief Gets the size of the underlying units.
  inline constexpr size_t count() { return m_sections.size(); }

  /// @brief Gets the avialable testing sections.
  inline const $::Map::Dict<Handle::Group *> &sections() const noexcept { return m_sections; }

  /// @brief Gets and sets the current group-target.
  inline constexpr Handle::Group *target() const noexcept { return m_target; }
  inline auto target(Handle::Group *group) {
    return m_target = group, $::Lambda::Defer([&] { m_target = nullptr; });
  }

  /**
   * @brief Handles constructing a test-suite.
   * @param resource                  Section resource.
   */
  inline Handle::Group *suite(const $::URI::View &resource) { return suite(resource.relative().string(), resource); }
  inline Handle::Group *suite(const Details &location = {}) {
    return suite(location.resource().relative().string(), location);
  }

  /**
   * @brief Handles constructing a test-suite.
   * @param title                     Suite title.
   * @param location                  Location details.
   */
  inline Handle::Group *suite(const $::String::Buffer &title, const Details &location = {}) {
    if (m_sections.contains(title)) return m_sections.at(title); // ignore if already built
    return m_sections.emplace(title, m_build<Handle::Group>(title, location)).first->second;
  }

  /**
   * @brief Handles constructing a test-group.
   * @param title                     Title of group.
   * @param location                  Source location.
   */
  inline Handle::Group *group(const $::String::Buffer &title, const Details &location = {}) {
    auto *group = m_build<Handle::Group>(title, location);
    return m_emplace(location, group), group; // emplace group
  }

  /**
   * @brief Handles constructing a test-case.
   * @param title                     Title of case.
   * @param callback                  Handle callback.
   * @param location                  Source location.
   */
  inline Handle::Case *test(const $::String::Buffer &title, Handle::Callback &&callback, const Details &location = {}) {
    auto *test = m_build<Handle::Case>(title, location, std::move(callback));
    return m_emplace(location, test), test; // emplace the test now to be used
  }

  /**
   * @brief Constructs a test-case.
   * @param title                 Test title.
   * @param callback              Test callback.
   * @param location              Source location.
   */
  inline Bench::Mark *bench(const $::String::Buffer &title, Handle::Callback &&callback, const Details &location = {}) {
    auto *bench = m_build<Bench::Mark>(title, location, std::move(callback));
    return m_emplace(location, bench), bench; // emplace the test now to be used
  }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles emplacing storage values.
   * @param test                  Test to bind.
   */
  template <std::derived_from<Handle::Base> T, class... As> inline T *m_build(As &&...args) {
    auto test = $::Unique::New<T>(std::forward<As>(args)...);
    auto *reference = test.get(); // prepare reference here
    return m_handles.emplace_back(std::move(test)), reference;
  }

  /**
   * @brief Handles resolving the underlying target.
   * @param key                   Target key.
   */
  inline Handle::Group *m_resolve(const Details &location) { return m_resolve(location.resource()); }
  virtual inline Handle::Group *m_resolve(const $::URI::View &resource) {
    return m_target ? m_target : suite(resource);
  }

  /**
   * @brief Handles emplacing the underlying target.
   * @param key                   Target key.
   * @param test                  Test to emplace.
   */
  inline void m_emplace(const Details &location, const Handle::Base *test) { m_emplace(location.resource(), test); }
  inline void m_emplace(const $::URI::View &resource, const Handle::Base *test) {
    if (auto *group = m_resolve(resource)) group->emplace(test);
  }
};

} // namespace XT::Session

#endif
