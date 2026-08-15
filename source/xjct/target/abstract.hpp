#ifndef _XJCT_TARGET_ABSTRACT_HPP
#define _XJCT_TARGET_ABSTRACT_HPP

/// XJCT Modules
#include "xjct/archive/binary.hpp"
#include "xjct/archive/options.hpp"

namespace XJCT::Target {

/// @brief An injectable target.
struct $_ABSTRACT Abstract {
  //  CONSTRUCTORS  //

  /// @brief Virtual abstract destructor.
  virtual ~Abstract() = default;

  //  PUBLIC METHODS  //

  /// @brief Gets the imbuement format.
  inline constexpr Archive::Format format() const noexcept { return m_format(); }

  /**
   * @brief Gets a resource from a target.
   * @param name              Name of resource.
   */
  inline Blob::View resource(const $::String::View &name) const noexcept { return m_resource(name); }

  /**
   * @brief Handles codesigning a file.
   * @param binary            Binary file-path.
   */
  inline bool codesign(const $::FS::Path &binary) const noexcept { return m_codesign(binary); }

  /**
   * @brief Handles imbuing the library instance.
   * @param binary            Binary to imbue.
   * @param options           Imbument options.
   */
  inline bool imbue(Archive::Binary &binary, const Imbue::Options &options) const noexcept {
    return m_imbue(binary, options);
  }

protected:
  //  PRIVATE METHODS  //

  /// @brief The type of target format.
  virtual Archive::Format m_format() const noexcept = 0;

  /**
   * @brief Handles codesigning a file.
   * @param binary            Binary file-path.
   */
  virtual bool m_codesign(const $::FS::Path &) const noexcept { return true; }

  /**
   * @brief Gets a resource from a target.
   * @param name              Name of resource.
   */
  virtual Blob::View m_resource(const $::String::View &) const noexcept { return {}; }

  /**
   * @brief Handles imbuing the target.
   * @param binary            Binary to imbue.
   * @param options           Imbument options.
   */
  virtual bool m_imbue(Archive::Binary &binary, const Imbue::Options &options) const noexcept = 0;
};

} // namespace XJCT::Target

#endif
