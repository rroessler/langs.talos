#ifndef _TALOS_DEBUGGER_BREAKPOINT_HPP
#define _TALOS_DEBUGGER_BREAKPOINT_HPP

/// Talos Modules
#include "talos/forward/debugger.hpp"

namespace Talos::Debugger {

    /// @brief Breakpoint Declaration.
    struct Breakpoint : public $::Strong::Unit<uint64_t, Breakpoint>, public $::Printable {
        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructors.
        using Unit::Unit;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles safely printing breakpoints.
         * @param os                    Output stream.
         * @param self                  Breakpoint value.
         */
        static inline void m_print($::Stream::Output& os, const Breakpoint& self) {
            os << "BP[" << self.m_underlying() << ']';
        }
    };

}  // namespace Talos::Debugger

#endif
