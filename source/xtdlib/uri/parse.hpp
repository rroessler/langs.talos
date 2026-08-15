#ifndef _XTDLIB_URI_PARSE_HPP
#define _XTDLIB_URI_PARSE_HPP

/// Library Includes
#include "xtdlib/uri/buffer.hpp"

namespace $::URI {

/**
 * @brief Handles parsing URI values.
 * @param view                      View to parse.
 */
Buffer Parse(const String::View &view);

} // namespace $::URI

#endif
