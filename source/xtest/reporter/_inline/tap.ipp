#ifndef _XTEST_REPORTER_TAP_IPP
#define _XTEST_REPORTER_TAP_IPP

/// Testing Includes
#include "xtest/reporter/stream.hpp"

namespace XT::Reporter {

/// @brief TAP Reporter Implementation.
template <> class Proxy<Label::TAP> : public Stream {
  //  PROPERTIES  //

public:
  //  CONSTRUCTORS  //

  /// @brief Inherit the base constructor.
  using Stream::Stream;
};

} // namespace XT::Reporter

#endif
