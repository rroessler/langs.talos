#ifndef _TALOS_MEMBER_DESCRIPTOR_HPP
#define _TALOS_MEMBER_DESCRIPTOR_HPP

/// Talos Includes
#include "talos/forward/member.hpp"
#include "talos/forward/runtime.hpp"
#include "talos/forward/value.hpp"

namespace Talos::Member {

/// @brief Any Valid Descriptor.
using View = Descriptor *;

/// @brief The baseline descriptor.
class $_ABSTRACT Descriptor {
  //  PROPERTIES  //

  /// @brief Denotes internal mutability.
  bool m_readonly = false;

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs a baseline descriptor.
  constexpr Descriptor() = default;

  /**
   * @brief Constructs a descriptor.
   * @param readonly          Readonly flag.
   */
  constexpr Descriptor(bool readonly) : m_readonly(readonly) {}

  /// @brief Virtual abstract destructor.
  virtual ~Descriptor() = default;

  //  PUBLIC METHODS  //

  /// @brief Gets the current readonly state.
  inline constexpr bool readonly() const noexcept { return m_readonly; }

  /**
   * @brief Handles getting the value.
   * @param isolate           Runtime isolate.
   * @param self              Self value.
   */
  virtual Value::Any getter(Runtime::Isolate *isolate, const Value::Any &self) const = 0;

  /**
   * @brief Handles setting the value.
   * @param isolate           Runtime isolate.
   * @param self              Self value.
   * @param value             Value to assign.
   */
  virtual Value::Any setter(Runtime::Isolate *isolate, const Value::Any &self, const Value::Any &value) = 0;
};

} // namespace Talos::Member

#endif
