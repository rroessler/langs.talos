#ifndef _TALOS_SYNTAX_METADATA_HPP
#define _TALOS_SYNTAX_METADATA_HPP

/// Talos Includes
#include "talos/lexer/buffer.hpp"
#include "talos/module/metadata.hpp"
#include "talos/syntax/tree.hpp"

namespace Talos::Module {

/// @brief Constructs a set of syntax metadata.
template <> class Metadata::Wrapper<Phase::PARSED> : public Metadata {
  //  PROPERTIES  //

  /// @brief Associated tokens buffer.
  Lexer::Buffer m_tokens = Lexer::Buffer();

  /// @brief Associated syntax tree.
  $::Unique::Pointer<Syntax::Tree> m_tree = $::Unique::New<Syntax::Tree>();

public:
  //  CONSTRUCTORS  //

  /// @brief Constructs a set of exports.
  explicit Wrapper() = default;

  //  PUBLIC METHODS  //

  inline constexpr Lexer::Buffer &tokens() noexcept { return m_tokens; }
  inline constexpr const Lexer::Buffer &tokens() const noexcept { return m_tokens; }

  inline constexpr $::Unique::Pointer<Syntax::Tree> &tree() noexcept { return m_tree; }
  inline constexpr const Syntax::Tree *tree() const noexcept { return m_tree.get(); }
};

} // namespace Talos::Module

#endif
