#ifndef _XTDLIB_UTILITY_GLOBAL_HPP
#define _XTDLIB_UTILITY_GLOBAL_HPP

/// Library Modules
#include "xtdlib/mutex/lock.hpp"
#include "xtdlib/mutex/types.hpp"
#include "xtdlib/pointer/new.hpp"

namespace $::Global {

    /// @brief Storage for global singletons.
    template <Ptr::Ensure T>
    static inline constexpr std::pair<Ptr::Shared<T>&, Mutex::Auto&> storage() {
        static auto mutex = Mutex::Auto();
        static Ptr::Shared<T> s_instance = nullptr;
        return { s_instance, mutex };  // prepare output
    }

    /// @brief Allows accessing a globally initialized value.
    template <Ptr::Ensure T, class... As>
    static inline constexpr T* get(As&&... args) {
        auto [instance, mutex] = storage<T>();  // get the storage
        $_UNUSED $_AUTO = Lock::guard(mutex);   // and lock the getter
        if ($_LIKELY(instance != nullptr)) return instance.get();
        return (instance = New().shared<T>(std::forward<As>(args)...)).get();
    }

}  // namespace $::Global

#endif
