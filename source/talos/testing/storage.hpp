#ifndef _TALOS_TESTING_STORAGE_HPP
#define _TALOS_TESTING_STORAGE_HPP

/// Talos Includes
#include "talos/testing/options.hpp"

namespace Talos::Testing {

/// @brief Testing Storage.
struct Storage : public XI::Transient, XT::Session::Storage {
  //  CONSTRUCTORS  //

  /// @brief Constructs a defaulted set of storage.
  constexpr Storage() = default;
};

} // namespace Talos::Testing

#endif
