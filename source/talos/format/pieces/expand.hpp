#ifndef _TALOS_FORMAT_EXPAND_HPP
#define _TALOS_FORMAT_EXPAND_HPP

/// Format Includes
#include "talos/format/mixin.hpp"

namespace Talos::Format {

/// @brief Explicit Empty Piece.
struct Piece::Expand : public Piece::Mixin<Expand> {
  //  CONSTRUCTORS  //

  /// @brief Forces parent to expand/break.
  explicit Expand() = default;

protected:
  //  PRIVATE METHODS  //

  /**
   * @brief Handles writing a node.
   * @param writer                Format writer.
   * @param wrapping              Current wrapping.
   */
  void m_render(Writer *writer, Wrap wrapping) const noexcept final;

  /**
   * @brief Gets the width of a node.
   * @param wrapped               Wrapped groups.
   * @param force                 Forced width flag.
   */
  size_t m_width(const Wrap::List &wrapped, bool force) const noexcept final;
};

} // namespace Talos::Format

#endif