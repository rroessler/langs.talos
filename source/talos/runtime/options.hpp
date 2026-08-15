#ifndef _TALOS_RUNTIME_OPTIONS_HPP
#define _TALOS_RUNTIME_OPTIONS_HPP

/// Talos Includes
#include "talos/forward/runtime.hpp"

/// Options Includes
#include "talos/diagnostic/options.hpp"
#include "talos/forward/async.hpp"
#include "talos/garbage/options.hpp"
#include "talos/heap/options.hpp"
#include "talos/locale/options.hpp"
#include "talos/relint/options.hpp"
#include "talos/testing/options.hpp"

namespace Talos::Runtime {

/// @brief Runtime Services Container.
struct Options : public XI::Singleton {
  //  PROPERTIES  //

  /// @brief Available Runtime Flags.
  struct {
    bool lint = false;     // Enables linting.
    bool verbose = false;  // Hide verbose output.
    bool unstable = false; // Enable unstable APIs.

    bool optless = false;  // Disable all optimizations.
    bool jitless = false;  // Disable JIT compilation.
    bool typeless = false; // Disable all type-checks.
  } flags;

  /// @brief Available Runtime Dumps.
  struct {
    bool syntax = false;   // Show syntax dumps.
    bool types = false;    // Show type dumps.
    bool graphs = false;   // Show CFG dumps.
    bool bytecode = false; // Show bytecode dumps.
    bool assembly = false; // Show machine-code dumps.
  } dump;

  /// @brief Entry-script options.
  struct {
    $::String::Buffer entry = ".";              // Entry-script.
    std::vector<$::String::Buffer> argv = {};   // Variadic arguments.
    std::vector<$::String::Buffer> dotenv = {}; // Environment files.
  } script;

  /// @brief Heap runtime options.
  Heap::Options heap = {};

  /// @brief Asynchronous runtime options.
  Async::Options async = {};

  /// @brief Linter analysis options.
  Relint::Options linter = {};

  /// @brief Locale runtime options.
  Locale::Options locale = {};

  /// @brief Garbage collection options.
  Garbage::Options garbage = {};

  /// @brief Unit testing options.
  Testing::Options testing = {};

  /// @brief Diagnostic reporter options.
  Diagnostic::Options diagnostics = {};

  //  CONSTRUCTORS  //

  /// @brief Constructs a set of defaulted options.
  constexpr Options() = default;
};

} // namespace Talos::Runtime

#endif
