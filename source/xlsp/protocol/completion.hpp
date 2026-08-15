#ifndef _XLSP_PROTOCOL_COMPLETION_HPP
#define _XLSP_PROTOCOL_COMPLETION_HPP

/// XLSP Includes
#include "xlsp/protocol/range.hpp"

namespace XLSP {

/// @brief Text Document Completion.
struct Completion {
  //  TYPEDEFS  //

  /// @brief Available completion kinds.
  enum class Kind : uint8_t {
    TEXT = 1,
    METHOD = 2,
    FUNCTION = 3,
    CONSTRUCTOR = 4,
    FIELD = 5,
    VARIABLE = 6,
    CLASS = 7,
    INTERFACE = 8,
    MODULE = 9,
    PROPERTY = 10,
    UNIT = 11,
    VALUE = 12,
    ENUM = 13,
    KEYWORD = 14,
    SNIPPET = 15,
    COLOR = 16,
    FILE = 17,
    REFERENCE = 18,
    FOLDER = 19,
    VARIANT = 20,
    CONSTANT = 21,
    STRUCT = 22,
    EVENT = 23,
    OPERATOR = 24,
    TPARAM = 25
  };

  //  PROPERTIES  //

  /// @brief The kind of completion.
  Kind kind = Kind::TEXT;

  /// @brief Label of the completion item.
  $::String::Buffer label;

  //  CONSTRUCTORS  //

  /// @brief Do not allow empty completion items.
  constexpr Completion() = delete;

  /**
   * @brief Constructs an empty completion.
   * @param label             Completion label.
   * @param kind              Kind of completion.
   */
  constexpr Completion(const $::String::Buffer &label, Kind kind = Kind::TEXT) : kind(kind), label(label) {}

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles encoding a completion.
   * @param self                      Completion to encode.
   */
  static $::Serde::Value m_encode(const Completion &self) { return {{"kind", self.kind}, {"label", self.label}}; }
};

} // namespace XLSP

#endif
