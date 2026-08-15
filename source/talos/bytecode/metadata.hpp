#ifndef _TALOS_BYTECODE_METADATA_HPP
#define _TALOS_BYTECODE_METADATA_HPP

/// Talos Modules
#include "talos/function/info.hpp"
#include "talos/module/metadata.hpp"
#include "talos/runtime/isolate.hpp"

namespace Talos::Module {

/// @brief Constructs a set of bytecode metadata.
template <> class Metadata::Wrapper<Phase::COMPILED> : public Metadata {
  //  PROPERTIES  //

  /// @brief Associated output arena.
  $::Unique::Pointer<Image::Arena> m_arena = $::Unique::New<Image::Arena>();

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs a set of compilation exports.
  explicit Wrapper() = default;

  //  PUBLIC METHODS  //

  /// @brief Image compilation outputs.
  inline constexpr $::Unique::Pointer<Image::Arena> &arena() noexcept { return m_arena; }
  inline constexpr const Image::Arena *arena() const noexcept { return m_arena.get(); }
};

} // namespace Talos::Module

#endif
