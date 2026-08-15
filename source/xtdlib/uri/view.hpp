#ifndef _XTDLIB_URI_VIEW_HPP
#define _XTDLIB_URI_VIEW_HPP

/// Library Includes
#include "xtdlib/uri/alias.hpp"

namespace $::URI {

/// @brief Core URI view of the form "<scheme>:[//<authority>]<body>".
class View {
  //  PROPERTIES  //

  /// @brief Reference URI buffer.
  const Buffer *m_buffer = nullptr;

public:
  //  CONSTRUCTORS  //

  /// @brief An empty resource view.
  constexpr View() : m_buffer(Buffer::m_anonymous()) {}

  /**
   * @brief Constructs a URI view.
   * @param buffer                Buffer instance.
   */
  constexpr View(const Buffer &buffer) : m_buffer(&buffer) {}
  constexpr View(const Buffer *buffer) : m_buffer(buffer) { $_ASSERT(buffer); }

  //  OPERATOR METHODS  //

  /// @brief Checks if a URI is equal to another.
  inline constexpr bool operator==(const View &other) const noexcept { return *m_buffer == *other.m_buffer; }

  //  PUBLIC METHODS  //

  /// @brief Clones the underlying buffer instance.
  inline constexpr const Buffer &buffer() const noexcept { return *m_buffer; }

  /// @brief Gets a simple view of the URI.
  inline constexpr String::View view() const noexcept { return m_buffer->view(); }

  /// @brief Gets a raw view of the underlying URI value.
  inline constexpr String::Buffer raw() const noexcept { return m_buffer->raw(); }

  /// @brief Gets a reference to the scheme.
  inline constexpr String::View scheme() const noexcept { return m_buffer->scheme(); }

  /// @brief Gets the entire body value.
  inline constexpr String::View body() const noexcept { return m_buffer->body(); }

  /// @brief Gets the underlying authority value.
  inline constexpr String::View authority() const noexcept { return m_buffer->authority(); }

  /// @brief Directly denotes if using an anonymous view.
  inline constexpr bool anonymous() const noexcept { return m_buffer->anonymous(); }

  /**
   * @brief Gets the relative display view.
   * @param hint                      Optional hint.
   */
  inline constexpr FS::Path relative(const FS::Path &hint = Path::current()) const { return m_buffer->relative(hint); }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Dumps the current resource value.
   * @param os                        Output stream.
   * @param self                      URI instance.
   */
  static inline void m_print(std::ostream &os, const View &self) { os << *self.m_buffer; }
};

} // namespace $::URI

//  SPECIALIZATIONS  //

template <> struct ankerl::unordered_dense::hash<$::URI::Buffer> {
  using is_avalanching = void; // declare that this is not avalanchable
  $_NODISCARD uint64_t operator()(const $::URI::Buffer &uri) const noexcept {
    return hash<$::String::View>()(uri.view());
  }
};

template <> struct ankerl::unordered_dense::hash<$::URI::View> {
  using is_avalanching = void; // declare that this is not avalanchable
  $_NODISCARD uint64_t operator()(const $::URI::View &uri) const noexcept {
    return hash<$::String::View>()(uri.view());
  }
};

#endif
