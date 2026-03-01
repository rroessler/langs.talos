#ifndef _XLSP_MESSAGE_JSON_HPP
#define _XLSP_MESSAGE_JSON_HPP

/// XLSP Modules
#include "xlsp/forward/message.hpp"

namespace XLSP::JRPC {

    //  PROPERTIES  //

    static constexpr $::String::View KEY = "jsonrpc";              // Messages key.
    static constexpr $::String::View VERSION = "2.0";              // JRPC Version.
    static constexpr $::String::View LENGTH = "Content-Length: ";  // Content-length string.

#if $_PLATFORM_WINDOWS
    static constexpr $::String::View EOM = "\n\n";  // windows auto-injects '\r'
#else
    static constexpr $::String::View EOM = "\r\n\r\n";  // otherwise needs full EOM
#endif

}  // namespace XLSP::JRPC

#endif
