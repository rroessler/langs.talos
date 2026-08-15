#ifndef _TALOS_ATTRIBUTE_INTERNAL_HPP
#define _TALOS_ATTRIBUTE_INTERNAL_HPP

/// Talos Includes
#include "talos/diagnostic/inspect.hpp"

/// Syntax Includes
#include "talos/syntax/declaration/attribute.hpp"

namespace Talos::Syntax {

/// @brief Compile Time Deprecation Node.
class Internal : public Mixin<Internal, Attribute> {
  //  PROPERTIES  //

  /// @brief The feature to be enabled.
  Reflect::Feature m_feature;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a internal attribute.
   * @param feature                 Feature key.
   */
  explicit Internal(Reflect::Feature feature) : Mixin(Reflect::Category::INTERNAL), m_feature(feature) {}

  //  PUBLIC METHODS  //

  /// @brief The underlying attribute feature.
  inline constexpr Reflect::Feature feature() const noexcept { return m_feature; }
};

} // namespace Talos::Syntax

#endif
