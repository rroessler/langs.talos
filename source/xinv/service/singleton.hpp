#ifndef _XINV_SERVICE_SINGLETON_HPP
#define _XINV_SERVICE_SINGLETON_HPP

/// XINV Includes
#include "xinv/service/abstract.hpp"

namespace XI {

/// @brief Shared Service Abstraction.
struct $_ABSTRACT Singleton : public Abstract {
  //  CONSTRUCTORS  //

  /// @brief Virtual abstract destructor.
  virtual ~Singleton() = default;
};

} // namespace XI

#endif
