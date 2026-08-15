#ifndef _TALOS_MACHINE_MACROS_IPP
#define _TALOS_MACHINE_MACROS_IPP

/// Talos Includes
#include "talos/machine/visitor.hpp"

/// Machine Includes
#include "talos/machine/_inline/glue.ipp"

//  MACROS  //

/// @brief We expose our compiler methods with a specialized prefix.
#define __cc__ builder->compiler->

/// @brief We expose our emitter methods with a specialized prefix.
#define __ee__ builder->emitter->

#define TALOS_MM_MACHINE_EMIT(N, B, I, ...)                         \
  template <>                                                       \
  void Talos::Machine::Visitor::accept<Talos::Bytecode::Glyph::N>(  \
      Builder * B, const Bytecode::Qualified<Bytecode::Glyph::N> *I \
  )

#endif
