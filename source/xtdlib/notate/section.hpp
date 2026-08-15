#ifndef _XTDLIB_NOTATE_SECTION_HPP
#define _XTDLIB_NOTATE_SECTION_HPP

/// Library Includes
#include "xtdlib/notate/options.hpp"

/// Forward Declarations
$_FWD($::Notate, class Section)

/// Forward Definitions
$_FWD($::Notate, using Block = std::vector<Section>)
$_FWD($::Notate, using Segments = std::vector<String::View>)

namespace $::Notate {

/// @brief Documentation Section Structure.
class Section {
  //  TYPEDEFS  //

  /// @brief Internal dispatch structure.
  struct Dispatch;

  /// @brief Allow parsing internal access.
  friend Block Parse(const Segments &, const Options &);

  //  PROPERTIES  //

  /// @brief Encapsulated content segments.
  Segments m_segments = {};

  /// @brief The description leading offset.
  uint8_t m_describe = 0;

  /// @brief The encoded section label.
  uint16_t m_label = 0;

  /// @brief The encoded section parameter.
  uint16_t m_param = 0;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a section (typically from singular comment lines).
   * @param segments                  Section content.
   */
  constexpr Section(const Segments &segments = {}) : m_segments(segments) {}

  //  PUBLIC METHODS  //

  /// @brief Denotes if the section is empty.
  inline constexpr bool empty() const noexcept { return m_segments.empty(); }

  /// @brief Gets a view of the available segments.
  inline constexpr const Segments &segments() const noexcept { return m_segments; }

  /// @brief Constructs a section tag based on internal size.
  inline constexpr String::View label() const noexcept { return m_decode(m_label); }

  /// @brief Constructs a section name based on internal size.
  inline constexpr String::View parameter() const noexcept { return m_decode(m_param); }

  /// @brief Allow merging the description together.
  inline constexpr String::Buffer description() const noexcept {
    // prepare a suitable set of segments now
    auto revised = Segments(m_segments);

    // update the leading segment based on the description offset
    if (revised.size()) revised.front().remove_prefix(m_describe);

    // return the resulting description now
    return fmt::format("{0}", fmt::join(revised, "\n"));
  }

private:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles decoding components.
   * @param encoded                   Encoded offsets.
   */
  inline constexpr String::View m_decode(uint16_t encoded) const noexcept {
    // stop if there is no suitable leading segment
    if (m_segments.empty()) return {};

    // prepare the starting and ending offsets
    auto start = encoded >> 8;
    auto ending = encoded & 0xFF;

    // use the encoded offsets to slice the required item
    return m_segments.front().substr(start, ending - start);
  }
};

} // namespace $::Notate

#endif