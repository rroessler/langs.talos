#ifndef _CRATES_PACKAGE_MEMORY_HPP
#define _CRATES_PACKAGE_MEMORY_HPP

/// Talos Modules
#include <talos/dylib/registry.hpp>

//  X-MACROS  //

#define CRATE_XX_MEMORY_METHODS(X) \
    X(heap_avail)                  \
    X(heap_total)                  \
    X(heap_usage)

//  NAMESPACES  //

namespace Talos::Package {

    /// @brief Memory Package Addon.
    struct Memory : public Dylib::Proxy<"Memory"> {
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an assertion library.
         * @param isolate               Runtime isolate.
         * @param exports               Addon exports.
         */
        explicit Memory(Runtime::Isolate* isolate, Dylib::Exports& exports);

       private:
        //  PRIVATE METHODS  //

#define X(N, ...) static Value::Any m_##N(Runtime::Isolate* isolate, const Function::Arguments& args);
        CRATE_XX_MEMORY_METHODS(X)
#undef X
    };

}  // namespace Talos::Package

#endif
