#ifndef _TALOS_BYTECODE_VISITOR_HPP
#define _TALOS_BYTECODE_VISITOR_HPP

/// Talos Modules
#include "talos/bytecode/allocator.hpp"
#include "talos/bytecode/compiler.hpp"
#include "talos/syntax/visitor.hpp"

/// Forward Declarations
$_FWD(Talos::Bytecode, using Visitor = Syntax::Visitor<void, Compiler *, Register::Slot>)

//  MACROS  //

#define TALOS_MM_LOWER_NODE(T, N, C, D, ...)                         \
  template <>                                                        \
  void Talos::Bytecode::Visitor::Acceptor::accept<Talos::Syntax::T>( \
      const Syntax::T *N, Bytecode::Compiler *C, Register::Slot D    \
  )

//  NAMESPACES  //

namespace Talos::Syntax {

/// @brief Visitor Specialization.
template <> struct Visitor<void, Bytecode::Compiler *, Register::Slot>::Acceptor {
  //  TYPEDEFS  //

  /// @brief Allow fast access to syllables.
  using Glyph = Bytecode::Glyph;

  //  PUBLIC METHODS  //

  template <std::derived_from<Node> T>
  static void accept(const T *node, Bytecode::Compiler *compiler, Register::Slot destination);
};

} // namespace Talos::Syntax

//  SPECIALIZATIONS  //

#define X(T, ...) TALOS_MM_LOWER_NODE(T, , , );
TALOS_XX_SYNTAX_NODES(X)
#undef X

#endif
