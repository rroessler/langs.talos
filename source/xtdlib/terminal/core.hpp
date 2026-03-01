#ifndef _XTDLIB_TERMINAL_CORE_HPP
#define _XTDLIB_TERMINAL_CORE_HPP

/// LIbrary Modules
#include "xtdlib/stream/types.hpp"

namespace $::Terminal {

    /**
     * @brief Checks if a file-handle is a TTY.
     * @param fh                    File-handle to query.
     */
    bool is(int32_t fh);

    /**
     * @brief Checks if a file is a TTY.
     * @param file                  File to query.
     */
    bool is(Stream::Handle* file);

    /**
     * @brief Checks if a stream is a TTY.
     * @param stream                Stream to query.
     */
    bool is(const Stream::Output& stream);

    /**
     * @brief Casts a stream to a TTY.
     * @param stream                Stream to query.
     */
    Stream::Handle* as(const Stream::Output& stream);

}  // namespace $::Terminal

#endif
