#ifndef _XTEST_TRIVIA_LOCATION_HPP
#define _XTEST_TRIVIA_LOCATION_HPP

/// Testing Includes
#include "xtest/forward/trivia.hpp"

namespace XT::Trivia {

/// @brief Testing Location.
class Location {
  //  PROPERTIES  //

  size_t m_line = 0;   // Line of location.
  size_t m_column = 0; // Column of location.

  /// @brief Resource buffer to be encapsulated.
  $::URI::Buffer m_resource = {};

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs from a source-location.
   * @param location                    Baseline location.
   */
  constexpr Location(const $::Source::Location &location = {}) :
      Location(location.file(), location.line(), location.column()) {}

  /**
   * @brief Constructs a trivia location.
   * @param file                        File path.
   * @param line                        Line of location.
   * @param column                      Column of location.
   */
  constexpr Location(const $::String::View &file, size_t line = 0, size_t column = 0) :
      Location($::URI::File(file), line, column) {}

  /**
   * @brief Constructs a trivia location.
   * @param resource                    File resource.
   * @param line                        Line of location.
   * @param column                      Column of location.
   */
  constexpr Location(const $::URI::View &resource, size_t line = 0, size_t column = 0) :
      Location(resource.buffer(), line, column) {}

  /**
   * @brief Constructs a trivia location.
   * @param resource                    File resource.
   * @param line                        Line of location.
   * @param column                      Column of location.
   */
  constexpr Location(const $::URI::Buffer &resource, size_t line = 0, size_t column = 0) :
      m_line(line), m_column(column), m_resource(resource) {}

  //  PUBLIC METHODS  //

  /// @brief Gets the line number.
  inline constexpr size_t line() const noexcept { return m_line; }

  /// @brief Gets the column number.
  inline constexpr size_t column() const noexcept { return m_column; }

  /// @brief Gets the resource value.
  inline constexpr $::URI::View resource() const noexcept { return m_resource; }

  /// @brief Denotes if not attached to a file.
  inline constexpr bool anonymous() const noexcept { return m_resource.anonymous(); }

  /// @brief Gets the base file-name.
  inline constexpr $::String::Buffer filename() const noexcept { return $::Path::filename(m_resource.body()).string(); }

  /**
   * @brief Gets the relative resource.
   * @param hint                      Optional hint.
   */
  inline constexpr $::String::Buffer relative(const $::FS::Path &hint = $::System::cwd()) const noexcept {
    return m_resource.relative(hint).string();
  }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles dumping locations.
   * @param os                        Output stream.
   * @param self                      Location instance.
   */
  static inline void m_print(std::ostream &os, const Location &self) {
    os << self.relative(); // prepare the base details now before showing
    if (self.line() > 0) os << ':' << self.line() << ':' << self.column();
  }
};

} // namespace XT::Trivia

#endif
