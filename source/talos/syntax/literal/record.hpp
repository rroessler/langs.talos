#ifndef _TALOS_LITERAL_RECORD_HPP
#define _TALOS_LITERAL_RECORD_HPP

/// Syntax Includes
#include "talos/syntax/declaration/variable.hpp"

namespace Talos::Syntax {

/// @brief Record Literal Node.
class Record : public Mixin<Record, Expression> {
  //  PROPERTIES  //

  /// @brief Record elements.
  std::vector<Variable *> m_elements = {};

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a list literal.
   * @param elements                Record elements.
   */
  explicit Record(const std::vector<Variable *> &elements = {}) : m_elements(elements) {}

  //  PUBLIC METHODS  //

  inline constexpr bool empty() const noexcept { return m_elements.empty(); }
  inline constexpr size_t size() const noexcept { return m_elements.size(); }
  inline constexpr const std::vector<Variable *> &elements() const noexcept { return m_elements; }
};

} // namespace Talos::Syntax

#endif
