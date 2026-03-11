#ifndef _CRATES_PACKAGE_TOML_HPP
#define _CRATES_PACKAGE_TOML_HPP

/// Talos Modules
#include <talos/dylib/registry.hpp>
#include <talos/runtime/isolate.hpp>

//  X-MACROS  //

#define CRATE_XX_TOML_METHODS(X) \
    X(encode)                    \
    X(decode)

//  NAMESPACES  //

namespace Talos::Package {

    /// @brief TOML Package Addon.
    struct TOML : public Dylib::Proxy<"toml"> {
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a "toml" library.
         * @param isolate               Runtime isolate.
         * @param exports               Addon exports.
         */
        explicit TOML(Runtime::Isolate* isolate, Dylib::Exports& exports);

       private:
        //  PRIVATE METHODS  //

#define X(N, ...) static Value::Any m_##N(Runtime::Isolate* isolate, const Function::Arguments& args);
        CRATE_XX_TOML_METHODS(X)
#undef X
    };

}  // namespace Talos::Package

#endif
