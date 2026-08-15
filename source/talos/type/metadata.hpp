#ifndef _TALOS_TYPE_METADATA_HPP
#define _TALOS_TYPE_METADATA_HPP

/// Talos Includes
#include "talos/module/metadata.hpp"
#include "talos/relint/exports.hpp"
#include "talos/type/exports.hpp"

namespace Talos::Module {

/// @brief Constructs a set of typed metadata.
template <> class Metadata::Wrapper<Phase::TYPED> : public Metadata {
  //  PROPERTIES  //

  /// @brief Linting Mirror Exports.
  $::Unique::Pointer<Relint::Exports> m_mirrors = $::Unique::New<Relint::Exports>();

  /// @brief Type Environment Exports.
  $::Unique::Pointer<Type::Exports> m_exports = $::Unique::New<Type::Exports>(Type::New::any());

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs a set of exports.
  explicit Wrapper() = default;

  //  PUBLIC METHODS  //

  /// @brief Gets the internal type exports.
  inline constexpr $::Unique::Pointer<Type::Exports> &exports() noexcept { return m_exports; }
  inline constexpr const Type::Exports *exports() const noexcept { return m_exports.get(); }

  /// @brief Gets the internal mirror exports
  inline constexpr $::Unique::Pointer<Relint::Exports> &mirrors() noexcept { return m_mirrors; }
  inline constexpr const Relint::Exports *mirrors() const noexcept { return m_mirrors.get(); }
};

} // namespace Talos::Module

#endif
