#ifndef _TALOS_FORMAT_EMPTY_HPP
#define _TALOS_FORMAT_EMPTY_HPP

/// Format Includes
#include "talos/format/pieces/unicode.hpp"

namespace Talos::Format {

/// @brief Explicit Empty Node.
struct Piece::Empty : public Piece::Mixin<Empty, Unicode> {
  //  CONSTRUCTORS  //

  /// @brief A node that is always empty.
  explicit Empty() = default;
};

} // namespace Talos::Format

#endif