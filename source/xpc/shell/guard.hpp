#ifndef _XPC_SHELL_GUARD_HPP
#define _XPC_SHELL_GUARD_HPP

/// XPC Modules
#include "xpc/forward/shell.hpp"

namespace XPC::Shell {

    /// @brief Shell Guard.
    class Guard {
        //  PROPERTIES  //

        /// @brief The previously cached working directory.
        $::String::Buffer m_cached = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Caches the current working directory, then update the next.
         * @param incoming              Incoming directory.
         */
        constexpr Guard(const $::String::View& incoming) {
            if (incoming.empty()) return;  // ignore
            m_cached = $::System::cwd();   // previous
            if (m_cached == incoming) m_cached = "";
            else $::System::cwd(incoming);  // valid
        }

        /// @brief Handles resetting the previous cwd.
        constexpr ~Guard() {
            // ignore if there was no cached value at all
            if (!m_cached.empty()) $::System::cwd(m_cached);
        }
    };

}  // namespace XPC::Shell

#endif
