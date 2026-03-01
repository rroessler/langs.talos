#ifndef _XTDLIB_UNION_ALIGNED_HPP
#define _XTDLIB_UNION_ALIGNED_HPP

/// C++ Modules
#include <algorithm>

/// Library Modules
#include "xtdlib/macros/attributes.hpp"

namespace $::Union {

    /**
     * @brief Allows storage of any types.
     * @tparam Ts                       Types to inherit.
     */
    template <class... Ts>
    struct Aligned {
        //  PROPERTIES  //

        /// @brief Aligned underlying storage.
        $_ALIGNAS(Ts...) uint8_t buffer[std::max({ sizeof(Ts)... })];
    };

}  // namespace $::Union

#endif
