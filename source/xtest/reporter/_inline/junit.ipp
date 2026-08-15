#ifndef _XTEST_REPORTER_JUNIT_IPP
#define _XTEST_REPORTER_JUNIT_IPP

/// Testing Includes
#include "xtest/reporter/stream.hpp"

namespace XT::Reporter {

/// @brief JUNIT Reporter Implementation.
template <> class Proxy<Label::JUNIT> : public Stream {
  //  PROPERTIES  //

public:
  //  CONSTRUCTORS  //

  /// @brief Inherit the base constructor.
  using Stream::Stream;
};

} // namespace XT::Reporter

#endif
