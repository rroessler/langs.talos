#ifndef _XTEST_REPORTER_JSON_HPP
#define _XTEST_REPORTER_JSON_HPP

/// XT Modules
#include "xtest/reporter/stream.hpp"

namespace XT::Reporter {

    /// @brief JSON Reporter.
    template <>
    class Proxy<Tag::JSON> : public Stream {
        //  PROPERTIES  //

       public:
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Stream::Stream;
    };

}  // namespace XT::Reporter

#endif
