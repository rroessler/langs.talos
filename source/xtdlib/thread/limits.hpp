#ifndef _XTDLIB_THREAD_LIMITS_HPP
#define _XTDLIB_THREAD_LIMITS_HPP

/// C++ Includes
#include <thread>

namespace $::Thread::Limits {

    //  PUBLIC METHODS  //

    /// @brief Explicitly available hardware concurrency.
    static inline size_t hardware() noexcept { return std::thread::hardware_concurrency(); }

}  // namespace $::Thread::Limits

#endif
