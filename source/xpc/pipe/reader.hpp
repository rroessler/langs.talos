#ifndef _XPC_PIPE_READER_HPP
#define _XPC_PIPE_READER_HPP

/// XPC Includes
#include "xpc/pipe/unique.hpp"

namespace XPC::Pipe {

/// @brief Pipe Reader Interface.
struct Reader : public Unique {
  //  CONSTRUCTORS  //

  /// @brief Inherit the base constructors.
  using Unique::Unique;

  //  PUBLIC METHODS  //

  /// @brief Attempts to read strings.
  inline constexpr std::vector<uint8_t> flush() {
    // ignore if we have an invalid pipe
    if (invalid()) return {};

    // prepare a buffer to contain the output
    uint8_t buffer[BUFSIZ] = {};

    // prepare the output string as well
    auto output = std::vector<uint8_t>();

    // attempt reading the entire pipe-buffer
    for (ptrdiff_t transferred;;) {
      if ((transferred = m_read(buffer, BUFSIZ)) <= 0) break; // stop
      output.insert(output.end(), &buffer[0], &buffer[transferred]);
    }

    // and return the result now
    return output;
  }

  /// @brief Handles converting a flushed buffer into a string.
  inline constexpr $::String::Buffer string() {
    auto data = flush(); // prepare now
    return {data.begin(), data.end()};
  }

private:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles reading into a buffer.
   * @param buffer            Buffer to read into.
   * @param size              Size allowed to read.
   */
  ptrdiff_t m_read(void *buffer, size_t size);
};

} // namespace XPC::Pipe

#endif
