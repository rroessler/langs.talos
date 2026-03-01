#ifndef _XTDLIB_STRONG_INFER_HPP
#define _XTDLIB_STRONG_INFER_HPP

/// Library Modules
#include "xtdlib/traits/concepts.hpp"

namespace $::Strong {

    /// @brief Encapsulates any strong-type.
    template <class U, class T>
    class Base {
        //  TYPEDEFS  //

        using Tagged = T;      // Tagged typing.
        using Underlying = U;  // Underlying typing.

        /// @brief Allow inference internal access.
        template <class>
        friend struct Infer;
    };

    /// @brief Inference Accessor.
    template <class T>
    struct Infer {
        //  TYPEDEFS  //

        using Tagged = T::Tagged;          // Tagged typing.
        using Underlying = T::Underlying;  // Underlying typing.
    };

}  // namespace $::Strong

#endif
