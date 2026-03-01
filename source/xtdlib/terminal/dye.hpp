#ifndef _XTDLIB_TERMINAL_DYE_HPP
#define _XTDLIB_TERMINAL_DYE_HPP

/// Library Modules
#include "xtdlib/stream/types.hpp"

namespace $::Dye {

    //  PUBLIC METHODS  //

    /// @brief Gets the global enablement.
    bool enabled();

    /**
     * @brief Sets the global enablement.
     * @param state                 State to set.
     */
    void enabled(bool state);

    /**
     * @brief Gets the streams enablement.
     * @param stream                Output stream.
     */
    bool enabled(Stream::Handle* stream);

    /**
     * @brief Gets the streams enablement.
     * @param stream                Output stream.
     */
    bool enabled(Stream::Output& stream);

    /**
     * @brief Sets the streams enabled.
     * @param stream                Output stream.
     * @param state                 State to set.
     */
    Stream::Output& enabled(Stream::Output& stream, bool state);

}  // namespace $::Dye

#endif
