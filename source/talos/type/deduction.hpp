#ifndef _TALOS_TYPE_DEDUCTION_HPP
#define _TALOS_TYPE_DEDUCTION_HPP

/// Talos Includes
#include "talos/flow/passable.hpp"
#include "talos/type/registry.hpp"

namespace Talos::Type {

/// @brief Type Deduction Result.
struct Deduction {
  //  PROPERTIES  //

  /// @brief Resultant type.
  Erased type = New::any();

  /// @brief Flow control node.
  Control flow = nullptr;

  //  CONSTRUCTORS  //

  /// @brief Constructs a baseline deduction.
  constexpr Deduction() = default;

  /**
   * @brief Constructs a passable deduction.
   * @param type                  Type to pass.
   */
  template <std::derived_from<Unit> T>
  constexpr Deduction(const $::Shared::Pointer<T> &type) : Deduction(type, $::Unique::New<Flow::Passable>()) {}

  /**
   * @brief Constructs a passable deduction.
   * @param type                  Type to pass.
   * @param flow                  Flow to pass.
   */
  constexpr Deduction(const Erased &type, Control &&flow) : type(type), flow(std::move(flow)) {}
};

} // namespace Talos::Type

#endif
