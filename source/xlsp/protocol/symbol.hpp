#ifndef _XLSP_PROTOCOL_SYMBOL_HPP
#define _XLSP_PROTOCOL_SYMBOL_HPP

/// XLSP Includes
#include "xlsp/protocol/range.hpp"

namespace XLSP {

/// @brief Text Document Symbol.
struct Symbol {
  //  TYPEDEFS  //

  /// @brief Available Symbol Kinds.
  enum class Kind : uint8_t {
    UNKNOWN = 0,
    FILE = 1,
    MODULE = 2,
    NAMESPACE = 3,
    PACKAGE = 4,
    CLASS = 5,
    METHOD = 6,
    PROPERTY = 7,
    FIELD = 8,
    CONSTRUCTOR = 9,
    ENUM = 10,
    INTERFACE = 11,
    FUNCTION = 12,
    VARIABLE = 13,
    CONSTANT = 14,
    STRING = 15,
    NUMBER = 16,
    BOOLEAN = 17,
    ARRAY = 18,
    OBJECT = 19,
    KEY = 20,
    VOID = 21,
    VARIANT = 22,
    STRUCT = 23,
    EVENT = 24,
    OPERATOR = 25,
    TPARAM = 26,
  };

  //  PROPERTIES  //

  /// @brief Kind of symbol.
  Kind kind = Kind::UNKNOWN;

  /// @brief Deprecation state.
  bool deprecated = false;

  /// @brief Base range of symbol.
  Range range = {};

  /// @brief Selection range of symbol.
  Range selection = {};

  /// @brief Name of the symbol.
  $::String::Buffer name = {};

  /// @brief Bound symbols to this one.
  std::vector<Symbol> children = {};

  //  CONSTRUCTORS  //

  /// @brief Constructs invalid symbols.
  constexpr Symbol() = default;

  /**
   * @brief Constructs a document symbol.
   * @param name                      Name of symbol.
   * @param kind                      Kind of symbol.
   */
  constexpr Symbol(const $::String::View &name, Kind kind = Kind::UNKNOWN) : kind(kind), name(name) {}

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles encoding a document symbol.
   * @param self                      Symbol to encode.
   */
  static $::Serde::Value m_encode(const Symbol &self) {
    // construct the basis of our symbol
    $::Serde::Object symbol = {
        {"name", self.name},
        {"kind", self.kind},
        {"range", $::Serde::Encode(self.range)},
        {"selectionRange", $::Serde::Encode(self.selection)},
    };

    // bind the optional details as well
    if (self.deprecated) symbol["tags"] = {1};
    if (self.children.size()) symbol["children"] = $::Serde::Encode(self.children);

    // and resolve our symbol
    return symbol;
  }
};

} // namespace XLSP

#endif
