#ifndef _XTDLIB_URI_CODEC_HPP
#define _XTDLIB_URI_CODEC_HPP

/// C++ Modules
#include <cstdint>

/// Library Modules
#include "xtdlib/macros/forward.hpp"
#include "xtdlib/string/buffer.hpp"
#include "xtdlib/string/view.hpp"

/// Forward Declarations
$_FWD(class Buffer, $::URI)

namespace $::URI::Codec {

    /**
     * @brief Denotes if a character should be escaped.
     * @param ch                        Character to check.
     */
    bool escape(uint8_t ch);

    /**
     * @brief Handles parsing a URI buffer.
     * @param buffer                    URI to parse.
     */
    Buffer parse(const String::View& buffer);

    /**
     * @brief Handles decoding "%" encoded URI's.
     * @param buffer                    Buffer to decode.
     */
    Buffer decode(const String::View& buffer);

    /**
     * @brief Handles encoding "%" encoded URI's.
     * @param resource                  Resource to encode.
     */
    String::Buffer encode(const Buffer& resource);

}  // namespace $::URI::Codec

#endif
