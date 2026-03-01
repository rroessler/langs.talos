#ifndef _XTDLIB_ALLOCATORY_STANDARD_HPP
#define _XTDLIB_ALLOCATORY_STANDARD_HPP

/// C++ Modules
#include <limits>

/// Library Includes
#include "xtdlib/allocator/policy.hpp"
#include "xtdlib/allocator/tracker.hpp"

namespace $::Allocator {

    /// @brief Explicit Standard Policy.
    struct Policy::Standard {
        //  PUBLIC METHODS  //

        /// @brief Gets the policies maximum allocation size.
        static inline size_t max_size() { return std::numeric_limits<size_t>::max(); }

        /**
         * @brief Handles allocating tracable values.
         * @param count                 Total byte-count.
         * @param location              Source location.
         * @param category              Category to bind.
         */
        static inline void* allocate(size_t count, $_UNUSED const Location& location = Location(),
            $_UNUSED const Category& category = Category()) {
            void* pointer = static_cast<void*>(new uint8_t[count]);  // bind now
            return Tracker::acquire(pointer, Record(count, category, location));
        }

        /**
         * @brief Handles deallocating memory.
         * @param pointer               Pointer to bytes.
         */
        static inline void deallocate(void* pointer) {
            Tracker::release(pointer);  // release now
            delete[] (static_cast<uint8_t*>(pointer));
        }
    };

    // ensure the allocation policy is valid now
    static_assert(Policy::Validate<Policy::Standard>, "Policy::Standard fails");

}  // namespace $::Allocator

#endif
