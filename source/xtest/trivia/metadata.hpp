#ifndef _XTEST_TRIVIA_METADATA_HPP
#define _XTEST_TRIVIA_METADATA_HPP

/// Testing Includes
#include "xtest/trivia/location.hpp"

namespace XT::Trivia {

/// @brief Statistics Container.
struct Metadata {
  //  PROPERTIES  //

  bool todo = false; // Unimplemented flag.
  bool skip = false; // Skip request flag.

  Location location = {};       // Source location.
  $::String::Buffer title = {}; // Title descriptor.
};

} // namespace XT::Trivia

#endif
