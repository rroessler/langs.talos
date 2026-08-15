#ifndef _XTEST_REPORTER_XML_IPP
#define _XTEST_REPORTER_XML_IPP

/// Testing Includes
#include "xtest/reporter/stream.hpp"

namespace XT::Reporter {

/// @brief XML Reporter Implementation.
template <> class Proxy<Label::XML> : public Stream {
  //  PROPERTIES  //

public:
  //  CONSTRUCTORS  //

  /// @brief Inherit the base constructor.
  using Stream::Stream;
};

} // namespace XT::Reporter

#endif
