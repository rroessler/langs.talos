#ifndef _XSIO_CONTEXT_TRANSFER_HPP
#define _XSIO_CONTEXT_TRANSFER_HPP

/// XSIO Modules
#include "xsio/forward/context.hpp"

namespace XSIO::Context {

    /// @brief Context Transfer Object.
    struct Transfer {
        void* data;
        Pointer fctx;
    };

}  // namespace XSIO::Context

#endif
