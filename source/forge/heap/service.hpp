#ifndef _FORGE_HEAP_SERVICE_HPP
#define _FORGE_HEAP_SERVICE_HPP

/// Forge Modules
#include "forge/forward/garbage.hpp"
#include "forge/heap/buffer.hpp"
#include "forge/heap/options.hpp"
#include "forge/heap/spaces.hpp"
#include "forge/runtime/isolate.hpp"

namespace Forge::Heap {

    /// @brief Heap Service.
    class Service : public XI::Define<Service, XI::Shared, XI::Immediate> {
        //  TYPEDEFS  //

        /// @brief Allow GC internal access.
        friend class Garbage::Service;

        //  PROPERTIES  //

        /// @brief Heap access mutex.
        mutable $::Mutex::Auto m_mutex;

        /// @brief Heap address pointer.
        void* m_data = nullptr;

        /// @brief Encapsulated heap options.
        const Options* m_options;

        /// @brief Services container.
        XI::Container* m_services;

        /// @brief Bound allocation buffers.
        $::Map<const Async::Processor*, Buffer> m_buffers = {};

        /// @brief Internal heap-regions available.
        $::Ptr::Unique<Spaces> m_spaces = $::New().unique<Spaces>();

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a new heap-service.
         * @param services                  Services container.
         */
        explicit Service();
        explicit Service(XI::Container* services);

        /// @brief Handles destroying heaped memory.
        ~Service();

        //  PUBLIC METHODS  //

        /// @brief Gets the total available heap-space.
        inline constexpr size_t total() const noexcept { return Limits::ADDRESS_SPACE; }

        /// @brief Gets the available memory remaining.
        inline constexpr size_t available() const noexcept { return total() - usage(); }

        /// @brief Gets the current heap options available.
        inline constexpr const Options* options() const noexcept { return m_options; }

        /// @brief Gets the underlying heap-address.
        inline constexpr Address address() const noexcept { return std::bit_cast<Address>(m_data); }

        /// @brief Gets a view of the current garbage regions.
        inline constexpr const Spaces* regions() const noexcept { return m_spaces.get(); }

        /// @brief Grows the underlying heap.
        void grow();

        /// @brief Shrinks the underlying heap.
        void shrink();

        /// @brief Gets the current usage.
        size_t usage() const noexcept;

        /**
         * @brief Allows releasing a region (expected to be empty).
         * @param region                    REgion to remove.
         */
        Region* release(Region* region);

        /**
         * @brief Attempts aquiring a stage.
         * @param stage                     Stage to acquire.
         * @param parent                    Linked region.
         */
        Region* acquire(Stage stage, Region* parent = nullptr);

        /**
         * @brief Gets an isolates current allocator.
         * @param isolate                   Thread isolate.
         */
        inline constexpr Buffer* allocator(Runtime::Isolate* isolate) {
            return allocator(isolate->thread()->worker()->processor());
        }

        /**
         * @brief Gets a processors allocator.
         * @param processor                 Processor reference.
         */
        inline constexpr Buffer* allocator(const Async::Processor* processor) {
            if (m_buffers.contains(processor)) return &m_buffers.at(processor);
            return &m_buffers.emplace(processor, Buffer(this)).first->second;
        }

       private:
        //  PRIVATE METHODS  //

        /// @brief Unmaps free regions.
        void m_unmap();

        /// @brief Maps any free regions.
        Region* m_remap();

        /// @brief Pops any free regions.
        Region* m_pop();
    };

}  // namespace Forge::Heap

#endif
