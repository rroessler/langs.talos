#ifndef _XSIO_MEMORY_BUFFER_HPP
#define _XSIO_MEMORY_BUFFER_HPP

/// XSIO Includes
#include "xsio/forward/memory.hpp"

namespace XSIO::Memory {

/// @brief Guarded Memory Buffer.
class Buffer {
  //  PROPERTIES  //

  /// @brief Size of buffer.
  size_t m_size = 0;

  /// @brief Mapped memory data.
  void *m_data = nullptr;

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Constructs a guarded memory buffer.
   * @param size                      Size of memory.
   */
  constexpr Buffer(size_t size = 0) : m_size(size) { m_data = m_allocate(); }

  /// @brief Handles releasing the underlying data.
  constexpr ~Buffer() { m_release(); }

  //  PUBLIC METHODS  //

  /// @brief Gets the total size of the buffer.
  inline constexpr size_t size() const noexcept { return m_size; }

  /// @brief Gets the underlying capacity value.
  inline constexpr size_t capacity() const noexcept { return m_size + m_page() * 2; }

  /// @brief Gets the page-aligned data pointer.
  inline constexpr void *data() const noexcept { return reinterpret_cast<void *>(address()); }

  /// @brief Gets tht page-aligned data address.
  inline constexpr uintptr_t address() const noexcept { return reinterpret_cast<uintptr_t>(m_data) + m_page(); }

private:
  //  PRIVATE METHODS  //

  /// @brief Gets the underlying page size.
  inline constexpr size_t m_page() const noexcept { return $::Memory::Page::size(); }

  /// @brief Handles allocating the buffer.
  inline void *m_allocate() const noexcept {
    // ignore the size is currently empty or allocated already
    if (m_data != nullptr) return m_data;

    // prepare the memory protection to be used
    auto protection = $::Memory::Prot::READ | $::Memory::Prot::WRITE;

    // attempt allocating as necessary now to a mapped item
    return $::Memory::Map::alloc(nullptr, capacity(), protection);
  }

  /// @brief Handles releasing the buffer.
  inline void m_release() {
    if ($_UNLIKELY(m_data == nullptr)) return;
    $::Memory::Map::free(m_data, capacity());
    m_data = nullptr, m_size = 0; // clear
  }
};

} // namespace XSIO::Memory

#endif
