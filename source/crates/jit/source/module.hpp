#ifndef _CRATES_PACKAGE_JIT_HPP
#define _CRATES_PACKAGE_JIT_HPP

/// Talos Modules
#include <talos/dylib/registry.hpp>

//  X-MACROS  //

#define CRATE_XX_JIT_METHODS(X) X(compile)

//  NAMESPACES  //

namespace Talos::Package {

    /// @brief JIT Package Addon.
    struct JIT : public Dylib::Proxy<"JIT"> {
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an assertion library.
         * @param isolate               Runtime isolate.
         * @param exports               Addon exports.
         */
        explicit JIT(Runtime::Isolate* isolate, Dylib::Exports& exports);

       private:
        //  PRIVATE METHODS  //

#define X(N, ...) static Value::Any m_##N(Runtime::Isolate* isolate, const Function::Arguments& args);
        CRATE_XX_JIT_METHODS(X)
#undef X
    };

}  // namespace Talos::Package

#endif
