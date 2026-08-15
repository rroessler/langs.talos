#ifndef _TALOS_TYPE_LOOPABLE_HPP
#define _TALOS_TYPE_LOOPABLE_HPP

/// Type Includes
#include "talos/type/utility/transform.hpp"

namespace Talos::Type::Utility {

/// @brief Loopable Type Resolver.
struct Loopable {
  //  CONSTRUCTORS  //

  /// @brief Default constructor.
  explicit Loopable() = default;

  //  OPERATOR METHODS  //

  /**
   * @brief Handles awaiting a target.
   * @param target                Target to await.
   * @param constraints           Constraints to use.
   */
  Erased operator()(const Erased &target, Constraints *constraints) const noexcept;

private:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles awaiting a target.
   * @param target                Target to await.
   * @param constraints           Constraints to use.
   */
  Erased m_resolve(const Erased &target, Constraints *constraints) const noexcept;
};

/// @brief Ensure the resolution conversion is valid.
static_assert(std::convertible_to<Loopable, Resolver>);

} // namespace Talos::Type::Utility

#endif
