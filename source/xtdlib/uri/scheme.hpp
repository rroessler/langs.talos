#ifndef _XTDLIB_URI_SCHEME_HPP
#define _XTDLIB_URI_SCHEME_HPP

/// Library Includes
#include "xtdlib/string/view.hpp"

namespace $::URI::Scheme {

    //  PROPERTIES  //

    static constexpr String::View EVAL = "eval";
    static constexpr String::View FILE = "file";
    static constexpr String::View HREF = "href";
    static constexpr String::View HTTP = "http";
    static constexpr String::View HTTPS = "https";

}  // namespace $::URI::Scheme

#endif
