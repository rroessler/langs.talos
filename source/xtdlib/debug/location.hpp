#ifndef _XTDLIB_DEBUG_LOCATION_HPP
#define _XTDLIB_DEBUG_LOCATION_HPP

/// Library Includes
#include "xtdlib/filesystem/path.hpp"

namespace $::Source {

/// @brief Source Location Alias.
class Location {
  //  PROPERTIES  //

  /// @brief Location instance.
  std::source_location m_location;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a new source location.
   * @param source                    Source to bind.
   */
  constexpr Location(const std::source_location &source = std::source_location::current()) : m_location(source) {}

  //  PUBLIC METHODS  //

  inline constexpr size_t line() const noexcept { return m_location.line(); }
  inline constexpr size_t column() const noexcept { return m_location.column(); }
  inline constexpr String::View file() const noexcept { return m_location.file_name(); }
  inline constexpr String::View callee() const noexcept { return m_location.function_name(); }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles dumping locations.
   * @param os                        Output stream.
   * @param self                      Location instance.
   */
  static inline void m_print(std::ostream &os, const Location &self) {
    auto relative = Path::relative(self.file()); // prepare relative
    os << relative.string() << ':' << self.line() << ':' << self.column();
  }
};

} // namespace $::Source

#endif
