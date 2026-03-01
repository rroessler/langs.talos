#ifndef _XTDLIB_STREAM_COLOR_HPP
#define _XTDLIB_STREAM_COLOR_HPP

/// C++ Modules
#include <locale>

/// Library Modules
#include "xtdlib/stream/types.hpp"

namespace $::Facet {

    /// @brief Colored Facet Instance.
    struct Color final : public std::locale::facet {
        //  PROPERTIES  //

        /// @brief Coloring enablement.
        bool disabled = false;

        /// @brief Internally constructed ID.
        static std::locale::id id;

        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a colored locale.
         * @param stream                    Underlying stream.
         */
        Color(Stream::Output& os);

        /**
         * @brief Constructs a colored locale.
         * @param stream                    Underlying stream.
         */
        Color(Stream::Handle* stream);

        /**
         * @brief Constructs a colored locale.
         * @param enabled                    Enablement state.
         */
        Color(bool enabled) : std::locale::facet(0), disabled(!enabled) {}
    };

}  // namespace $::Facet

#endif
