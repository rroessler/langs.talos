#ifndef _TALOS_MACHINE_MACROS_IPP
#define _TALOS_MACHINE_MACROS_IPP

/// Talos Modules
#include "talos/machine/template.hpp"
#include "talos/machine/visitor.hpp"

//  MACROS  //

/// @brief Helper macro for defining templated outputs.
#define __tm__ Template::

/// @brief Helper macro for defining compilation outputs.
#define __cc__ builder->compiler->

/// @brief Helper macro for defining emitter outputs.
#define __ee__ builder->emitter.

/// @brief Allow converting values to immediates.
#define __iv__(V) Immediate(std::bit_cast<Reference>(V))

#endif
