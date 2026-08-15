#ifndef _XPC_PIPE_WRITER_HPP
#define _XPC_PIPE_WRITER_HPP

/// XPC Includes
#include "xpc/pipe/unique.hpp"

namespace XPC::Pipe {

/// @brief Pipe Writer Interface.
struct Writer : public Unique {
  //  CONSTRUCTORS  //

  /// @brief Inherit the base constructor.
  using Unique::Unique;

  //  PUBLIC METHODS  //

private:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles writing into a buffer.
   * @param buffer            Buffer to write from.
   * @param size              Size allowed to write.
   */
  ptrdiff_t m_write(const void *buffer, size_t size);
};

} // namespace XPC::Pipe

#endif
