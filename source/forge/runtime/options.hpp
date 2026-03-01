#ifndef _FORGE_RUNTIME_OPTIONS_HPP
#define _FORGE_RUNTIME_OPTIONS_HPP

/// Forge Modules
#include "forge/forward/async.hpp"
#include "forge/forward/runtime.hpp"

/// Forge Options
#include "forge/diagnostic/options.hpp"
#include "forge/garbage/options.hpp"
#include "forge/heap/options.hpp"
#include "forge/locale/options.hpp"
#include "forge/relint/options.hpp"
#include "forge/testing/options.hpp"

namespace Forge::Runtime {

    /// @brief Runtime Options.
    struct Options : public XI::Define<Options, XI::Shared> {
        //  PROPERTIES  //

        /// @brief Available Runtime Flags.
        struct {
            bool lint = false;      // Enables linting.
            bool verbose = false;   // Hide verbose output.
            bool unstable = false;  // Enable unstable APIs.

            bool small = false;     // Enforce stricter GC.
            bool optless = false;   // Disable all optimizations.
            bool jitless = false;   // Disable JIT compilation.
            bool typeless = false;  // Disable all type-checks.
        } flags;

        /// @brief Available Runtime Dumps.
        struct {
            bool syntax = false;     // Show syntax dumps.
            bool types = false;      // Show type dumps.
            bool graphs = false;     // Show CFG dumps.
            bool bytecode = false;   // Show bytecode dumps.
            bool machine = false;    // Show machine-code dumps.
            bool execution = false;  // Show profiling dumps.
        } dump;

        /// @brief Available Runtime Limits.
        struct {
            size_t backtraces = 10;  // Explicit backtraces limit.
        } limits;

        /// @brief Entry-script options.
        struct {
            $::String::Buffer entry = ".";               // Entry-script.
            std::vector<$::String::Buffer> argv = {};    // Variadic arguments.
            std::vector<$::String::Buffer> dotenv = {};  // Environment files.
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

}  // namespace Forge::Runtime

#endif
