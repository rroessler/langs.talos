#ifndef _XTEST_REPORTER_TAP_HPP
#define _XTEST_REPORTER_TAP_HPP

/// XT Modules
#include "xtest/reporter/stream.hpp"

namespace XT::Reporter {

    /// @brief TAP Reporter.
    template <>
    class Proxy<Tag::TAP> : public Stream {
        //  PROPERTIES  //

       public:
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Stream::Stream;
    };

}  // namespace XT::Reporter

#endif
