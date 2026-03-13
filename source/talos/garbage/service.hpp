#ifndef _TALOS_GARBAGE_SERVICE_HPP
#define _TALOS_GARBAGE_SERVICE_HPP

/// Talos Modules
#include "talos/forward/engine.hpp"
#include "talos/garbage/lifetimes.hpp"
#include "talos/garbage/marker.hpp"
#include "talos/garbage/options.hpp"
#include "talos/heap/region.hpp"

namespace Talos::Garbage {

    /// @brief Garbage Service.
    class Service : public XI::Define<Service, XI::Shared, XI::Immediate> {
        //  TYPEDEFS  //

        /// @brief Allow markers internal access.
        friend class Marker;

        //  PROPERTIES  //

        $::Atomic<size_t> m_cycle = 1;          // Cycle count.
        $::Atomic<bool> m_collectable = false;  // Collection flag.

        /// @brief Associated garbage mutex.
        mutable $::Mutex::Auto m_mutex;

        /// @brief Garbage options.
        const Options* m_options;

        /// @brief Services container.
        XI::Container* m_services;

        /// @brief The bound heap service.
        Heap::Service* m_heap;

        /// @brief The underlying marking queue.
        $::Ptr::Unique<Marker> m_marker = nullptr;

        /// @brief Handles disposable value lifetimes.
        $::Ptr::Unique<Lifetimes> m_lifetimes = nullptr;

        /// @brief Last collection timestamp.
        $::Chrono::Point m_ts = $::Chrono::Point();

        $::Set<Heap::Region*> m_juniors = {};  // Intermediate regions.
        $::Set<Heap::Region*> m_seniors = {};  // Senior heap-regions.

        /// @brief All objects to be deallocated.
        $::Set<Object::Header*> m_removable = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a garbage service.
         * @param services                  Services container.
         */
        explicit Service();
        explicit Service(XI::Container* services);

        //  PUBLIC METHODS  //

        /// @brief Gets the total collection cycles executed.
        inline constexpr size_t cycles() const noexcept { return m_cycle; }

        /// @brief Gets the disposable stack containers.
        inline constexpr Lifetimes* lifetimes() const noexcept { return m_lifetimes.get(); }

        /**
         * @brief Request a GC attempt.
         * @param major                     Force major collection.
         */
        void collect(bool major = false);

       private:
        //  PRIVATE METHODS  //

        /// @brief Handles deallocating heap resources.
        void m_deallocate();
        void m_deallocate(Object::Header* header);

        /// @brief Constructs the forwarding transformer.
        Globals::Callback m_forward();

        /**
         * @brief Handles encoding/decoding forwarded targets.
         * @param header                    Source header.
         */
        uint32_t m_encode(Object::Header* header) const noexcept;
        Object::Any m_decode(Object::Header* header) const noexcept;

        /**
         * @brief Core GC request handler.
         * @param major                     Force major collection.
         */
        void m_request(bool major);

        /**
         * @brief Handles GC collection routines.
         * @param mode                      Collection mode.
         */
        void m_collect(Mode mode);

        /**
         * @brief Handles marking all the roots.
         * @param mode                      Collection mode.
         */
        void m_mark(Mode mode);

        /**
         * @brief Handles updating references.
         * @param mode                      Collection mode.
         */
        void m_update(Mode mode);
        void m_update(Object::Header* header);

        /**
         * @brief Handles recycling collected heap regions.
         * @param mode                      Collection mode.
         */
        void m_recycle(Mode mode);

        /**
         * @brief Handles recyclying heap regions.
         * @param region                   Region reference.
         * @param cache                     Cached regions.
         */
        void m_recycle(Heap::Region* region);
        void m_recycle(Heap::Region* region, $::Set<Heap::Region*>& cache);
        void m_recycle(const $::Set<Heap::Region*>& regions, $::Set<Heap::Region*>& cache);

        /**
         * @brief Adjusts the heap depending on collection statistics.
         * @param mode                      Collection mode.
         */
        void m_adjust(Mode mode);
    };

}  // namespace Talos::Garbage

#endif
