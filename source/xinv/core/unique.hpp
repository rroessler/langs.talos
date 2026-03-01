#ifndef _XINV_CORE_TRANSIENT_HPP
#define _XINV_CORE_TRANSIENT_HPP

/// XINV Includes
#include "xinv/core/service.hpp"

namespace XI {

    /// @brief Unique Service Abstraction.
    struct $_ABSTRACT Unique : public Service {
        //  CONSTRUCTORS  //

        /// @brief Virtual abstract destructor.
        virtual ~Unique() = default;
    };

}  // namespace XI

#endif
