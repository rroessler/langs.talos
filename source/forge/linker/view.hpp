#ifndef _FORGE_LINKER_VIEW_HPP
#define _FORGE_LINKER_VIEW_HPP

/// Forge Modules
#include "forge/forward/linker.hpp"

namespace Forge::Linker {

    /// @brief Linker Address Typing.
    using Address = uintptr_t;

    /// @brief Linked Code View.
    class View {
        //  PROPERTIES  //

        /// @brief Gets the underlying size.
        size_t m_size = 0;

        /// @brief Encapsulated address value.
        size_t m_offset = 0;

        /// @brief The associated buffer value.
        const std::vector<uint8_t>* m_buffer = nullptr;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a buffer view.
         * @param offset                    Offset to bind.
         * @param size                      Size of the view.
         * @param buffer                    Internal buffer value.
         */
        constexpr View() = default;
        constexpr View(size_t offset, size_t size, const std::vector<uint8_t>* buffer) :
            m_size(size), m_offset(offset), m_buffer(buffer) {}

        //  PUBLIC METHODS  //

        /// @brief Handles validating the underlying address.
        inline constexpr bool valid() const noexcept { return m_buffer != nullptr; }

        /// @brief The size of the view.
        inline constexpr size_t size() const noexcept { return m_size; }

        /// @brief The offset from the start of the buffer.
        inline constexpr size_t offset() const noexcept { return m_offset; }

        /// @brief Gets the underlying address value.
        inline constexpr Address address() const noexcept {
            return m_buffer ? reinterpret_cast<Address>(m_buffer->data()) + m_offset : 0;
        }
    };

}  // namespace Forge::Linker

#endif
