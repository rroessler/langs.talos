#ifndef _TALOS_ANNOTATION_QUALIFIER_HPP
#define _TALOS_ANNOTATION_QUALIFIER_HPP

/// Syntax Includes
#include "talos/syntax/annotation/generics.hpp"
#include "talos/syntax/literal/identifier.hpp"

namespace Talos::Syntax {

/// @brief Qualifier Annotation.
class Qualifier : public Mixin<Qualifier, Annotation> {
  //  PROPERTIES  //

  /// @brief Generic template arguments.
  Specialization m_types = {};

  /// @brief Qualifier identifiers chain.
  std::vector<Identifier *> m_segments;

public:
  //  CONSTRUCTORS  //

  /// @brief Do not allow default construction.
  explicit Qualifier() = delete;

  /**
   * @brief Constructs a qualifier annotation.
   * @param segment                   Identifier segment.
   * @param types                     Typed arguments.
   */
  explicit Qualifier(Identifier *segment, const Specialization &types = {}) : m_types(types), m_segments({segment}) {}

  /**
   * @brief Constructs a qualifier annotation.
   * @param segments                  Identifier segments.
   * @param types                     Typed arguments.
   */
  explicit Qualifier(const std::vector<Identifier *> &segments, const Specialization &types = {})
      : m_types(types), m_segments(segments) {}

  //  PUBLIC METHODS  //

  inline constexpr const Specialization &types() const noexcept { return m_types; }
  inline constexpr const std::vector<Identifier *> &segments() const noexcept { return m_segments; }
};

} // namespace Talos::Syntax

#endif
