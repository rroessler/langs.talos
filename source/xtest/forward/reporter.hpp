#ifndef _XTEST_FORWARD_REPORTER_HPP
#define _XTEST_FORWARD_REPORTER_HPP

/// Vendor Modules
#include <xinv/xinv.hpp>

/// Forward Declarations
$_FWD(XT::Reporter, class Facade)
$_FWD(XT::Reporter, class Interface)

/// Forward Definitions
$_FWD(XT::Reporter, using Spinner = $::Functor::Shared<$::Spinner::Shared(XI::Container*)>)

//  X-MACROS  //

/// @brief Available Reporters.
#define XTEST_XX_REPORTERS_LIST(X) \
    X(TAP, true)                   \
    X(XML, true)                   \
    X(JSON, true)                  \
    X(JUNIT, true)                 \
    X(TEXT, false)

//  NAMESPACES  //

namespace XT::Reporter {

    /// @brief Available Reporter Tags.
    $_XX_ENUM_CLASS(Tag, uint8_t, XTEST_XX_REPORTERS_LIST, DEFAULT = TEXT);

    /// @brief Proxy-Based Reporters.
    template <Tag T>
    class Proxy;

}  // namespace XT::Reporter

#endif
