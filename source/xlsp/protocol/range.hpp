#ifndef _XLSP_PROTOCOL_RANGE_HPP
#define _XLSP_PROTOCOL_RANGE_HPP

/// XLSP Includes
#include "xlsp/protocol/position.hpp"

namespace XLSP {

/// @brief Range Structure.
struct Range {
  //  PROPERTIES  //

  Position start = {}; // Starting position.
  Position end = {};   // Ending position.

  //  CONSTRUCTORS  //

  /// @brief Constructs an empty range (0, 0) -> (0, 0).
  constexpr Range() = default;

  /**
   * @brief Constructs a range.
   * @param la                        Line alpha.
   * @param ca                        Column alpha.
   * @param lb                        Line beta.
   * @param cb                        Column beta.
   */
  constexpr Range(uint32_t la, uint32_t ca, uint32_t lb, uint32_t cb) : start(la, ca), end(lb, cb) {
    if (start > end) std::swap(start, end);
  }

  /**
   * @brief Constructs a range.
   * @param start                     Starting position.
   * @param end                       Ending position.
   */
  constexpr Range(const Position &start, const Position &end) : Range(start.line, start.column, end.line, end.column) {}

  /**
   * @brief Constructs a range.
   * @param alpha                     Alpha range.
   * @param beta                      Beta range.
   */
  constexpr Range(const Range &alpha, const Range &beta) :
      Range(alpha.start < beta.start ? alpha.start : beta.start, alpha.end < beta.end ? alpha.end : beta.end) {}

  //  OPERATOR METHODS  //

  /// @brief Equality operator for ranges.
  constexpr auto operator==(const Range &other) const { return start == other.start && end == other.end; }

  /// @brief Comparison operator for ranges.
  constexpr auto operator<=>(const Range &other) const {
    return std::tie(start, end) <=> std::tie(other.start, other.end);
  }

  //  PUBLIC METHODS  //

  /// @brief Gets a client version of a range.
  inline constexpr Range client() const noexcept { return Range(start.client(), end.client()); }

  /// @brief Gets a server version of a range.
  inline constexpr Range server() const noexcept { return Range(start.server(), end.server()); }

  /**
   * @brief Checks if a range contains a position.
   * @param position                Value to check.
   */
  inline constexpr bool contains(const Position &position) const noexcept {
    return position >= start && position <= end;
  }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles encoding ranges.
   * @param self                      Range instance.
   */
  static $::Serde::Object m_encode(const Range &self) {
    return {{"start", $::Serde::Encode(self.start)}, {"end", $::Serde::Encode(self.end)}};
  }

  /**
   * @brief Handles decoding ranges.
   * @param value                     JSON value to decode.
   */
  static Range m_decode(const $::Serde::Value &value) {
    return {$::Serde::Decode<Position>(value.at("start")), $::Serde::Decode<Position>(value.at("end"))};
  }

  /**
   * @brief Handles printing ranges.
   * @param os                        Output stream.
   * @param self                      Range to print.
   */
  static inline void m_print(std::ostream &os, const Range &self) { os << self.start << '-' << self.end; }
};

} // namespace XLSP

#endif
