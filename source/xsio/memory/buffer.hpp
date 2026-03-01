#ifndef _XSIO_MEMORY_BUFFER_HPP
#define _XSIO_MEMORY_BUFFER_HPP

/// XSIO Modules
#include "xsio/forward/memory.hpp"

namespace XSIO::Memory {

    /// @brief Guarded Memory Buffer.
    class Buffer {
        //  PROPERTIES  //

        size_t m_size = 0;       // Size of buffer.
        void* m_data = nullptr;  // Mapped memory data.

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a guarded memory buffer.
         * @param size                      Size of memory.
         */
        explicit Buffer(size_t size = 0) : m_size(size) { m_data = m_allocate(); }

        /// @brief Handles releasing the underlying data.
        ~Buffer() { m_release(); }

        //  PUBLIC METHODS  //

        inline constexpr size_t size() const noexcept { return m_size - m_page() * 2; }
        inline constexpr void* data() const noexcept { return reinterpret_cast<void*>(m_address()); }

       private:
        //  PRIVATE METHODS  //

        /// @brief Gets the underlying page size.
        inline constexpr size_t m_page() const noexcept { return $::Memory::Page::size(); }

        /// @brief Gets the underlying data as an address.
        inline constexpr uintptr_t m_address() const noexcept { return reinterpret_cast<uintptr_t>(m_data) + m_page(); }

        /// @brief Handles allocating the buffer.
        inline void* m_allocate() const noexcept {
            // ignore the size is currently empty or allocated already
            if (m_data != nullptr) return m_data;

            // resolve the outgoing size to be page-aligned
            auto size = m_size + m_page() * 2;

            // prepare the memory protection to be used
            auto protection = $::Memory::Prot::READ | $::Memory::Prot::WRITE;

            // attempt allocating as necessary now to a mapped item
            return $::Memory::Map::alloc(nullptr, size, protection);
        }

        /// @brief Handles releasing the buffer.
        inline void m_release() {
            // only release if the size and data is valid to do so
            if (m_data) $::Memory::Map::free(m_data, m_size + m_page() * 2), m_data = nullptr, m_size = 0;
        }
    };

}  // namespace XSIO::Memory

#endif
