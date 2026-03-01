#ifndef _XTEST_REPORTER_JUNIT_HPP
#define _XTEST_REPORTER_JUNIT_HPP

/// XT Modules
#include "xtest/reporter/stream.hpp"

namespace XT::Reporter {

    /// @brief JUnit Reporter.
    template <>
    class Proxy<Tag::JUNIT> : public Stream {
        //  PROPERTIES  //

       public:
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Stream::Stream;
    };

}  // namespace XT::Reporter

#endif
