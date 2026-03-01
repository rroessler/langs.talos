#ifndef _XTDLIB_ALLOCATOR_TRACKER_HPP
#define _XTDLIB_ALLOCATOR_TRACKER_HPP

/// C++ Includes
#include <numeric>

/// Library Includes
#include "xtdlib/allocator/record.hpp"
#include "xtdlib/container/map.hpp"
#include "xtdlib/mutex/types.hpp"
#include "xtdlib/utility/singleton.hpp"

namespace $::Allocator {

    /// @brief Memory Tracker Implementation.
    class Tracker : public Singleton<Tracker> {
        //  TYPEDEFS  //

        /// @brief Mapped entry types.
        using Entry = std::pair<void*, Record>;

        //  PROPERTIES  //

        /// @brief Denotes if recording allocations.
        bool m_recording = true;

        /// @brief Total accumulated allocations.
        size_t m_accumulated = 0;

        /// @brief Underlying tracker mutex.
        mutable Mutex::Auto m_mutex;

        /// @brief All memory-pool based allocations.
        std::vector<size_t> m_pooled = {};

        /// @brief Complete set of registered allocations.
        Map<void*, Record> m_allocations = {};

       protected:
        //  CONSTRUCTORS  //

        /// @brief Constructs a singleton tracker.
        explicit Tracker() = default;

       public:
        /// @brief Handles reporting any leaks on closing.
        ~Tracker() { m_report(), m_recording = false; }

        //  PUBLIC METHODS  //

        /// @brief Gets and sets the current recording state.
        static inline bool& enabled() noexcept { return s_instance()->m_recording; }

        /// @brief Gets the total allocated memory.
        static size_t total() { return s_instance()->m_accumulated; }

        /**
         * @brief Gets the total pooled amount.
         * @param pool                      Pool to query.
         */
        static size_t total(size_t pool) { return s_instance()->m_pooled[pool]; }

        /**
         * @brief Gets the total amount by category.
         * @param category                  Category to query.
         */
        static size_t total(const Category& category) {
            auto predicate = [category](const Entry& entry) { return entry.second.category() == category; };
            return std::ranges::count_if(s_instance()->m_allocations, predicate);  // count all the allocations
        }

        /**
         * @brief Handles tracing allocations of memory.
         * @param pointer                   Pointer to trace.
         * @param record                    Allocation record.
         */
        static void* acquire(void* pointer, const Record& record);

        /**
         * @brief Handles deallocation of memory.
         * @param pointer                   Pointer to remove.
         */
        static void release(void* pointer);

       private:
        //  PRIVATE METHODS  //

        /// @brief Handles reporting any leaks.
        void m_report() const;
    };

}  // namespace $::Allocator

#endif
