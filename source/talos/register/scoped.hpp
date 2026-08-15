#ifndef _TALOS_REGISTER_SCOPED_HPP
#define _TALOS_REGISTER_SCOPED_HPP

/// Talos Include
#include "talos/register/slot.hpp"

namespace Talos::Register {

/// @brief Temporary Register Instance.
class Scoped : public Slot {
  //  PROPERTIES  //

  /// @brief Underlying allocator reference.
  Bytecode::Allocator *m_allocator = nullptr;

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs a defaulted temporary register.
  using Slot::Slot;

  /**
   * @brief Constructs a temporary register.
   * @param allocator                 Allocator reference.
   */
  Scoped(Bytecode::Allocator *allocator);

  /// @brief Removes the volatile register.
  ~Scoped();
};

} // namespace Talos::Register

#endif
