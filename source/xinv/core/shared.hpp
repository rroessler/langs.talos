#ifndef _XINV_CORE_SINGLETON_HPP
#define _XINV_CORE_SINGLETON_HPP

/// XINV Includes
#include "xinv/core/service.hpp"

namespace XI {

    /// @brief Shared Service Abstraction.
    struct $_ABSTRACT Shared : public Service {
        //  CONSTRUCTORS  //

        /// @brief Virtual abstract destructor.
        virtual ~Shared() = default;
    };

}  // namespace XI

#endif
