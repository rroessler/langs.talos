#ifndef _TALOS_MODULE_PHASE_HPP
#define _TALOS_MODULE_PHASE_HPP

/// Talos Includes
#include "talos/forward/import.hpp"
#include "talos/forward/module.hpp"

namespace Talos::Module {

/// @brief Available Printing Dumps.
enum class Dump : uint8_t {
  SYNTAX,   // Show syntax-tree.
  TYPEDEFS, // Show final type-world.
  BYTECODE, // Show bytecode outputs.
};

/// @brief Module Runtime Phase.
enum class Phase : uint8_t {
  CLEANED,  // No available metadata.
  PARSED,   // Syntax has been parsed.
  TYPED,    // Type-checking completed.
  COMPILED, // Bytecode compilation done.
  EXPORTED, // Module has exported values.

  MAXIMUM = EXPORTED, // Artifacts total size.
};

} // namespace Talos::Module

#endif
