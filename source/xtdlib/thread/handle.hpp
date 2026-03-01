#ifndef _XTDLIB_THREAD_HANDLE_HPP
#define _XTDLIB_THREAD_HANDLE_HPP

/// Vendor Includes
#include <thread>

namespace $::Thread {

    /// @brief Auto-joinable thread value.
    using Auto = std::jthread;

    /// @brief Aliases thread handle value.
    using Handle = std::thread;

}  // namespace $::Thread

namespace $::Thread::This {

    /// @brief Alias the "this" thread namespace.
    using namespace std::this_thread;

}  // namespace $::Thread::This

#endif
