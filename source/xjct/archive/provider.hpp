#ifndef _XJCT_ARCHIVE_PROVIDER_HPP
#define _XJCT_ARCHIVE_PROVIDER_HPP

/// XJCT Modules
#include "xjct/sentinel/fuse.hpp"
#include "xjct/target/abstract.hpp"

namespace XJCT::Archive {

/// @brief Archive Provider.
struct Provider {
  //  CONSTRUCTORS  //

  /// @brief Constructs an archive provider.
  constexpr Provider() = default;

  //  PUBLIC METHODS  //

  /**
   * @brief Handles codesigning a binary.
   * @param binary                Executable file-path.
   */
  inline constexpr bool codesign(const $::FS::Path &binary) const noexcept {
    auto *target = m_resolve(); // resolve target
    return target ? target->codesign(binary) : true;
  }

  /**
   * @brief Handles imbuing the binary.
   * @param binary                Binary to imbue.
   * @param options               Imbuement options.
   */
  inline constexpr bool imbue(Binary &binary, const Imbue::Options &options) const noexcept {
    auto *target = m_resolve(binary); // resolve target
    return target ? target->imbue(binary, options) : false;
  }

  /**
   * @brief Handles defusing an executable of a fuse.
   * @param binary                Binary to imbue.
   * @param fuse                  Fuse to imbue.
   */
  inline constexpr bool defuse(Binary &binary, const $::String::View &fuse) const noexcept {
    return m_toggle(binary, fuse, false);
  }

  /**
   * @brief Handles infusing an executable with a fuse.
   * @param binary                Binary to imbue.
   * @param fuse                  Fuse to imbue.
   */
  inline constexpr bool infuse(Binary &binary, const $::String::View &fuse) const noexcept {
    return m_toggle(binary, fuse, true);
  }

  /**
   * @brief Handles defusing an executable of a fuse.
   * @param binary                Binary to imbue.
   * @param fuse                  Fuse to imbue.
   */
  inline constexpr bool defuse(Binary &binary, const Sentinel::View &fuse) const noexcept {
    return defuse(binary, fuse.prefix());
  }

  /**
   * @brief Handles infusing an executable with a fuse.
   * @param binary                Binary to imbue.
   * @param fuse                  Fuse to imbue.
   */
  inline constexpr bool infuse(Binary &binary, const Sentinel::View &fuse) const noexcept {
    return infuse(binary, fuse.prefix());
  }

  /**
   * @brief Handles resolving resources.
   * @param name                  Name of resource.
   */
  inline constexpr Blob::View resource(const $::String::View &name) const noexcept {
    auto *target = m_resolve(); // resolve target
    return target ? target->resource(name) : "";
  }

  /**
   * @brief Handles resolving resources.
   * @param fuse                  Resource fuse.
   */
  inline constexpr Blob::View resource(const Sentinel::View &fuse) const noexcept {
    return fuse.expect(), resource(fuse.name()); // ensure the fuse exists
  }

private:
  //  PRIVATE METHODS  //

  /**
   * @brief Prepares a binary imbument target.
   * @param binary                Binary to bind.
   */
  Target::Abstract *m_resolve() const noexcept;
  Target::Abstract *m_resolve(const Binary &binary) const noexcept;

  /**
   * @brief Handles toggling fuses.
   * @param binary                Binary to toggle.
   * @param prefix                Prefix fuse text.
   * @param state                 State to toggle.
   */
  bool m_toggle(Binary &binary, const $::String::View &prefix, bool state) const noexcept;
};

} // namespace XJCT::Archive

#endif
