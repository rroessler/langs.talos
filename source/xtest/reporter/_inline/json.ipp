#ifndef _XTEST_REPORTER_JSON_IPP
#define _XTEST_REPORTER_JSON_IPP

/// Testing Includes
#include "xtest/reporter/stream.hpp"

namespace XT::Reporter {

/// @brief JSON Reporter Implementation.
template <> class Proxy<Label::JSON> : public Stream {
  //  PROPERTIES  //

public:
  //  CONSTRUCTORS  //

  /// @brief Inherit the base constructor.
  using Stream::Stream;
};

} // namespace XT::Reporter

#endif
