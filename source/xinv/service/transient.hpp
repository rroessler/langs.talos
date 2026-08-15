#ifndef _XINV_SERVICE_TRANSIENT_HPP
#define _XINV_SERVICE_TRANSIENT_HPP

/// XINV Includes
#include "xinv/service/abstract.hpp"

namespace XI {

/// @brief Unique Service Abstraction.
struct $_ABSTRACT Transient : public Abstract {
  //  CONSTRUCTORS  //

  /// @brief Virtual abstract destructor.
  virtual ~Transient() = default;
};

} // namespace XI

#endif
