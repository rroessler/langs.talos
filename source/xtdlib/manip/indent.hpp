#ifndef _XTDLIB_MANIP_INDENT_HPP
#define _XTDLIB_MANIP_INDENT_HPP

/// Library Includes
#include "xtdlib/string/buffer.hpp"

namespace $::Manip {

/// @brief Indentation Instance.
struct Indent final : public std::streambuf {
  //  TYPEDEFS  //

  /// @brief Underlying traits for stream-buffers.
  using Traits = std::streambuf::traits_type;

  //  PROPERTIES  //

  /// @brief Prepare the current condition to be used.
  bool m_condition = true;

  String::Buffer m_padding; // Current indentation.
  std::ostream *m_owner;    // Owner stream instance.
  std::streambuf *m_dest;   // Destination buffer.

public:
  //  CONSTRUCTORS  //

  /**
   * @brief Encapsulates indenting an output buffer.
   * @param dest                      Buffer to indent.
   * @param level                     Current level to use.
   */
  explicit Indent(std::streambuf *dest, size_t level = 2) : m_padding(level, ' '), m_owner(nullptr), m_dest(dest) {}

  /**
   * @brief Encapsulates indenting an output stream.
   * @param owner                     Owner to indent.
   * @param level                     Current level to use.
   */
  explicit Indent(std::ostream &owner, size_t level = 2)
      : m_padding(level, ' '), m_owner(&owner), m_dest(owner.rdbuf()) {
    m_owner->rdbuf(this); // update the owner stream now to be used
  }

  /// @brief Ensures the destination buffer is resolved.
  ~Indent() {
    if (m_owner) m_owner->rdbuf(m_dest);
  }

protected:
  //  PRIVATE METHODS  //

  /// @brief Handles overflow conditions.
  Traits::int_type overflow(Traits::int_type ch) override {
    if (m_condition && ch != '\n') m_dest->sputn(m_padding.data(), m_padding.size());
    return m_condition = ch == '\n', m_dest->sputc(Traits::to_char_type(ch));
  }
};

} // namespace $::Manip

#endif