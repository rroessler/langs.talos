#ifndef _XTDLIB_STREAM_TYPES_HPP
#define _XTDLIB_STREAM_TYPES_HPP

/// C++ Includes
#include <iostream>

namespace $::Stream {

    using Handle = std::FILE;      // Native stream (C based).
    using Input = std::istream;    // Output stream (or writer).
    using Output = std::ostream;   // Input stream (or reader).
    using Duplex = std::iostream;  // Duplex stream (both).

}  // namespace $::Stream

#endif
