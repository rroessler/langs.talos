#ifndef _TALOS_LINKER_BUFFER_HPP
#define _TALOS_LINKER_BUFFER_HPP

/// Talos Modules
#include "talos/linker/records.hpp"
#include "talos/linker/view.hpp"

namespace Talos::Linker {

    /// @brief Linked Code Buffer.
    class Buffer {
        //  PROPERTIES  //

        /// @brief Available bytecode-lookup.
        Records m_sources = {};

        /// @brief Internal buffer value.
        std::vector<uint8_t> m_buffer = {};

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a code buffer.
         * @param capacity              Initial capacity.
         */
        constexpr Buffer(size_t capacity = 1024) { m_buffer.reserve(capacity); }

        /**
         * @brief Constructs a code buffer.
         * @param buffer                Code to emplace.
         */
        constexpr Buffer(const std::vector<uint8_t>& buffer) : m_buffer(buffer) {}

        //  PUBLIC METHODS  //

        inline constexpr bool empty() const noexcept { return m_buffer.empty(); }
        inline constexpr size_t size() const noexcept { return m_buffer.size(); }

        inline constexpr const uint8_t* data() const noexcept { return m_buffer.data(); }
        inline constexpr Address address() const noexcept { return reinterpret_cast<Address>(m_buffer.data()); }
        inline constexpr const std::vector<uint8_t>& buffer() const noexcept { return m_buffer; }

        inline constexpr Records& sources() noexcept { return m_sources; }
        inline constexpr const Records& sources() const noexcept { return m_sources; }

        /**
         * @brief Gets a view of the buffer.
         * @param offset                Offset value.
         * @param size                  Size of view.
         */
        inline constexpr View view(size_t offset = 0) const noexcept { return view(offset, size() - offset); }
        inline constexpr View view(size_t offset, size_t size) const noexcept { return View(offset, size, &m_buffer); }

        /**
         * @brief Writes a value to the buffer.
         * @param value                 Value to write.
         */
        template <std::unsigned_integral T>
        inline constexpr Buffer& write(T value) {
            auto* data = std::bit_cast<const uint8_t*>(&value);  // prepare data view
            for (size_t ii = 0; ii < sizeof(T); ++ii) m_buffer.emplace_back(data[ii]);
            return *this;  // and allow chaining writes for easier use
        }

        /**
         * @brief Patches a value to the buffer.
         * @param offset                Offset to patch.
         * @param value                 Value to write.
         */
        template <std::unsigned_integral T>
        inline constexpr Buffer& patch(size_t offset, T value) {
            auto* data = std::bit_cast<const uint8_t*>(&value);  // prepare data view
            for (size_t ii = 0; ii < sizeof(T); ++ii) m_buffer[offset + ii] = data[ii];
            return *this;  // and allow chaining writes for easier use
        }
    };

}  // namespace Talos::Linker

#endif
