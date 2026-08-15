#ifndef _XINV_Service_ABSTRACT_HPP
#define _XINV_Service_ABSTRACT_HPP

/// XINV Includes
#include "xinv/forward/core.hpp"

namespace XI {

/// @brief Base Service Abstraction.
struct $_ABSTRACT Abstract {
  //  CONSTRUCTORS  //

  /// @brief Virtual abstract destructor.
  virtual ~Abstract() = default;
};

} // namespace XI

#endif
