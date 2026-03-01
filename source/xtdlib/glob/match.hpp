#ifndef _XTDLIB_GLOB_MATCH_HPP
#define _XTDLIB_GLOB_MATCH_HPP

/// Library Modules
#include "xtdlib/string/view.hpp"
#include "xtdlib/vendors/aster.hpp"

namespace $::Glob {

    /**
     * @brief Handles a once-off glob-match.
     * @param glob          Glob pattern.
     * @param input         Input to match.
     */
    static inline constexpr bool Match(const String::View& glob, const String::View& input) {
        return Aster::Match::glob(glob, input);
    }

}  // namespace $::Glob

#endif
