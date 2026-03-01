#ifndef _XINV_CORE_SERVICE_HPP
#define _XINV_CORE_SERVICE_HPP

/// XINV Modules
#include "xinv/forward/core.hpp"

namespace XI {

    /// @brief Base Service Abstraction.
    struct $_ABSTRACT Service {
        //  CONSTRUCTORS  //

        /// @brief Virtual abstract destructor.
        virtual ~Service() = default;
    };

}  // namespace XI

#endif
