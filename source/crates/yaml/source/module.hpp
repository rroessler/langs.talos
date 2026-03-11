#ifndef _CRATES_PACKAGE_YAML_HPP
#define _CRATES_PACKAGE_YAML_HPP

/// Talos Modules
#include <talos/dylib/registry.hpp>
#include <talos/runtime/isolate.hpp>

//  X-MACROS  //

#define CRATE_XX_YAML_METHODS(X) \
    X(encode)                    \
    X(decode)

//  NAMESPACES  //

namespace Talos::Package {

    /// @brief YAML Package Addon.
    struct YAML : public Dylib::Proxy<"yaml"> {
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a "yaml" library.
         * @param isolate               Runtime isolate.
         * @param exports               Addon exports.
         */
        explicit YAML(Runtime::Isolate* isolate, Dylib::Exports& exports);

       private:
        //  PRIVATE METHODS  //

#define X(N, ...) static Value::Any m_##N(Runtime::Isolate* isolate, const Function::Arguments& args);
        CRATE_XX_YAML_METHODS(X)
#undef X
    };

}  // namespace Talos::Package

#endif
