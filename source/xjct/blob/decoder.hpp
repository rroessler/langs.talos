#ifndef _XJCT_BLOB_DECODER_HPP
#define _XJCT_BLOB_DECODER_HPP

/// XJCT Includes
#include "xjct/forward/blob.hpp"

namespace XJCT::Blob {

/// @brief Blob Decoder Abstraction.
template <class T> struct $_ABSTRACT Decoder {
  //  CONSTRUCTORS  //

  /// @brief Virtual abstract destructor.
  virtual ~Decoder() = default;

  //  PUBLIC METHODS  //

  /**
   * @brief Handles reading a blob.
   * @param blob                  Source blob to read.
   */
  inline constexpr T read(const View &blob) const noexcept { return m_decode(blob); }

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Reads into a data location.
   * @param output                Output to write to.
   * @param count                 Expected size.
   * @param source                Source state.
   */
  template <Value U> inline constexpr void m_read(U *output, size_t count, View &source) const noexcept {
    size_t size = sizeof(U) * count;
    std::memcpy(output, source.data(), size);
    source.remove_prefix(size); // trim
  }

  /**
   * @brief Reads a numeric value.
   * @param source                Source state.
   */
  template <Value U> inline constexpr U m_read(View &source) const noexcept {
    U output = 0; // prepare the output
    return m_read(&output, 1, source), output;
  }

  /**
   * @brief Reads into a vector.
   * @param source                Source state.
   */
  template <Value U> inline constexpr std::vector<U> m_span(View &source) const noexcept {
    return m_span<U>(m_read<size_t>(source), source);
  }

  /**
   * @brief Reads into a vector.
   * @param count                 Expected size.
   * @param source                Source state.
   */
  template <Value U> inline constexpr std::vector<U> m_span(size_t count, View &source) const noexcept {
    auto output = std::vector<U>(count); // prepare
    return m_read(output.data(), count, source), output;
  }

  /**
   * @brief Reads into a string-view.
   * @param source                Source state.
   */
  inline constexpr $::String::View m_view(View &source) const noexcept {
    return m_view(m_read<size_t>(source), source);
  }

  /**
   * @brief Reads into a string-view.
   * @param count                 Size of view.
   * @param source                Source state.
   */
  inline constexpr $::String::View m_view(size_t count, View &source) const noexcept {
    auto view = source.substr(0, count);
    return source.remove_prefix(count), view;
  }

  /**
   * @brief Handles reading blobs.
   * @param source                Decoding state to use.
   */
  virtual T m_decode(Blob::View source) const noexcept = 0;
};

} // namespace XJCT::Blob

#endif
