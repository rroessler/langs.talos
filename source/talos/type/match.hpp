#ifndef _TALOS_TYPE_MATCH_HPP
#define _TALOS_TYPE_MATCH_HPP

/// Talos Includes
#include "talos/type/deduction.hpp"

namespace Talos::Type {

/// @brief Match Statement Output.
struct Match {
  //  PROPERTIES  //

  /// @brief Denotes if a fallback was seen.
  bool fallback = false;

  /// @brief Outgoing match result (holds value type).
  Deduction result = New::any();
};

} // namespace Talos::Type

#endif
