#ifndef _XTEST_REPORTER_XML_HPP
#define _XTEST_REPORTER_XML_HPP

/// XT Modules
#include "xtest/reporter/stream.hpp"

namespace XT::Reporter {

    /// @brief XML Reporter.
    template <>
    class Proxy<Tag::XML> : public Stream {
        //  PROPERTIES  //

       public:
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Stream::Stream;
    };

}  // namespace XT::Reporter

#endif
