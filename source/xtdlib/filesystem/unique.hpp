#ifndef _XTDLIB_FILESYSTEM_UNIQUE_HPP
#define _XTDLIB_FILESYSTEM_UNIQUE_HPP

/// Library Includes
#include "xtdlib/filesystem/path.hpp"
#include "xtdlib/filesystem/write.hpp"

namespace $::FS {

/// @brief A move-only temporary file.
class Unique {
  //  PROPERTIES  //

  /// @brief The temporary file-path.
  Path m_path;

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs a unique path value.
  explicit Unique() : Unique($::Path::unique()) {}

  /**
   * @brief Constructs a unique file.
   * @param path                  Unique path.
   */
  explicit Unique(const Path &path) : m_path(path) { Touch(m_path); }

  /// @brief Do not allow copy-construction.
  Unique(const Unique &) = delete;

  /// @brief Allow moving unique files.
  Unique(Unique &&) = default;

  /// @brief Handles destroying the file.
  ~Unique() { std::filesystem::remove(m_path); }

  //  OPERATOR METHODS  //

  inline constexpr Unique &operator=(const Unique &) = delete;
  inline constexpr Unique &operator=(Unique &&) = default;

  //  PUBLIC METHODS  //

  /// @brief Gets the unique file-path.
  inline constexpr const Path &path() const noexcept { return m_path; }
};

} // namespace $::FS

#endif
