#ifndef _TALOS_HEAP_REGION_HPP
#define _TALOS_HEAP_REGION_HPP

/// Talos Modules
#include "talos/heap/options.hpp"
#include "talos/object/header.hpp"

//  X-MACROS  //

/// @brief Available region placements.
#define XX_REGION_STAGES(X) \
    X(UNUSED)               \
    X(EDEN)                 \
    X(JUNIOR)               \
    X(SENIOR)               \
    X(STACK)

//  NAMESPACES  //

namespace Talos::Heap {

    /// @brief Available region placements.
    $_XX_ENUM_CLASS(Stage, uint8_t, XX_REGION_STAGES);

    /// @brief Heap Callback Handler.
    using Callback = $::Functor::Shared<void(Object::Header*)>;

    /// @brief Region of Heap Memory.
    class $_ALIGNAS(Pointer::Alignment::OBJECT) Region {
        //  TYPEDEFS  //

        /// @brief Allow heap internal access.
        friend class Service;

        //  PROPERTIES  //

        /// @brief Currently used size.
        size_t m_used = 0;

        /// @brief The encoded parent/stage.
        Address m_address = m_encode(Stage::UNUSED);

       public:
        //  CONSTRUCTORS  //

        /// @brief Default constructor for regions.
        constexpr Region() = default;

        //  PUBLIC METHODS  //

        /// @brief Denotes the total used of a region.
        inline constexpr size_t used() const { return m_used; }

        /// @brief Denotes the current regions stage.
        inline constexpr Stage stage() const { return m_stage(m_address); }

        /// @brief Handles getting/setting parents.
        inline constexpr Region* parent() const { return m_parent(m_address); }
        inline constexpr void parent(Region* parent) { m_address = m_encode(stage(), parent); }

        /// @brief Gets the current remaining memory.
        inline constexpr size_t remaining() const { return Limits::REGIONS_SIZE - m_used; }

        /// @brief Gets the associated region identifier.
        inline constexpr size_t id() const { return (buffer() % Limits::ADDRESS_SPACE) / Limits::REGIONS_SIZE; }

        /// @brief Gets the current top of the region.
        inline constexpr Address head() const { return buffer() + m_used; }

        /// @brief Gets the address of the underlying buffer.
        inline constexpr Address buffer() const { return std::bit_cast<Address>(this) + sizeof(Region); }

        /** Handles clearing the region it encompasses. */
        inline void reset() noexcept { m_address = m_encode(Stage::UNUSED, parent()), m_used = 0; }

        /**
         * @brief Handles promoting regions.
         * @param stage                 Stage to promote.
         * @param parent                Parent to bind.
         */
        inline Stage promote(Stage stage) noexcept { return (m_address = m_encode(stage, parent())), stage; }
        inline Stage promote(Stage stage, Region* parent) noexcept {
            return (m_address = m_encode(stage, parent)), stage;
        }

        /**
         * @brief Determines if memory fits within the region.
         * @param size                  Size to be checked.
         */
        inline constexpr bool fits(size_t size) const noexcept { return size <= remaining(); }

        /**
         * @brief Handles iterating over each region item.
         * @param callback              Callback to execute.
         */
        inline void each(Callback&& callback) const noexcept {
            for (Address offset = buffer(); offset < m_used;) {
                auto* header = std::bit_cast<Object::Header*>(offset);
                callback(header), offset += header->size();  // get next
            }
        }

        /**
         * @brief Handles allocating memory on this region.
         * @param size                  Size of memory.
         */
        inline constexpr Address allocate(size_t size) {
            // pre-ensure the heap allocation will succeed
            $_ASSERT(fits(size), "Allocation of {0} bytes does not fit region", size);

            // prepare the starting and ending addresses
            Address start = buffer() + m_used;
            $_UNUSED Address end = start + size;

            // ensure some conditions are valid before continuing
            $_ASSERT(start % Pointer::Alignment::OBJECT == 0, "Allocation start-alignment failed");
            $_ASSERT(end % Pointer::Alignment::OBJECT == 0, "Allocation end-alignment failed");
            $_ASSERT(end <= buffer() + Limits::REGIONS_SIZE, "Allocation exceeds maximum region bounds");

            // increment the used space and return the allocation position
            return m_used += size, start;
        }

        /**
         * @brief Releases memory from this region.
         * @param size                  Size to releae.
         */
        inline constexpr size_t release(size_t size) {
            $_ASSERT(size <= m_used, "Release size larger than region");
            return m_used -= size;  // and should be able to remove now
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Decodes the stage.
         * @param encoded               Encoded address.
         */
        static inline constexpr Stage m_stage(Address encoded) noexcept {
            return static_cast<Stage>(encoded & Pointer::Mask::IMM);
        }

        /**
         * @brief Decodes the parent.
         * @param encoded               Encoded address.
         */
        static inline constexpr Region* m_parent(Address encoded) noexcept {
            return std::bit_cast<Region*>(encoded & ~Pointer::Mask::IMM);
        }

        /**
         * @brief Encodes the stage and parent.
         * @param stage                 Stage to encode.
         * @param parent                Parent to encode.
         */
        static inline constexpr Address m_encode(Stage stage, Region* parent = nullptr) {
            return std::bit_cast<Address>(parent) | static_cast<Address>(stage);
        }
    };

}  // namespace Talos::Heap

//  UNDEFINES  //

#undef XX_REGION_STAGES

#endif
