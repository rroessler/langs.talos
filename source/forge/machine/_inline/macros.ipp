#ifndef _FORGE_MACHINE_MACROS_IPP
#define _FORGE_MACHINE_MACROS_IPP

/// Forge Modules
#include "forge/machine/template.hpp"
#include "forge/machine/visitor.hpp"

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
