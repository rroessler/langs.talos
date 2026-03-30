#ifndef _XSIO_ASYNC_OPTIONS_HPP
#define _XSIO_ASYNC_OPTIONS_HPP

/// XSIO Modules
#include "xsio/forward/async.hpp"
#include "xsio/forward/timer.hpp"
#include "xsio/forward/virtual.hpp"
#include "xtdlib/memory/constants.hpp"

namespace XSIO::Async {

    /// @brief Asynchronous Runtime Options.
    struct Options {
        //  PROPERTIES  //

        /// @brief Available thread options.
        struct {
            /// @brief The maximum allowable stack-size.
            size_t stack_size = 8 * $::Memory::Size::MB;

            /// @brief The stack-underflow limit available.
            size_t stack_limit = 32 * $::Memory::Size::KB;

            /// @brief Time allowed before a thread is yielded.
            Timer::Ticks time_slice = 250ms;
        } thread;

        /// @brief Virtual processor options.
        struct {
            /// @brief The priority chance for random acquisition.
            size_t tasks_priority = 32;

            /// @brief The total processors allowed.
            size_t hardware_limit = $::Thread::Limits::hardware();
        } vprocs;

        /// @brief Available watchdog options.
        struct {
            /// @brief Force unsafe "detach" mode.
            bool unsafe_detach = true;

            /// @brief Wakeup interval to use.
            Timer::Ticks wakeup_interval = 10ms;
        } watchdog;

        /// @brief Available worker options.
        struct {
            /// @brief Expected idling time to be used.
            Timer::Ticks wait_time = 100ms;
        } worker;

        //  CONSTRUCTORS  //

        /// @brief Constructs a set of defaulted options.
        constexpr Options() = default;
    };

}  // namespace XSIO::Async

#endif
