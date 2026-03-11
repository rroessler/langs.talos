#ifndef _CRATES_PACKAGE_JSON_HPP
#define _CRATES_PACKAGE_JSON_HPP

/// Talos Modules
#include <talos/dylib/registry.hpp>
#include <talos/runtime/isolate.hpp>

//  X-MACROS  //

#define CRATE_XX_JSON_METHODS(X) \
    X(encode)                    \
    X(decode)

//  NAMESPACES  //

namespace Talos::Package {

    /// @brief JSON Package Addon.
    struct JSON : public Dylib::Proxy<"json"> {
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a "json" library.
         * @param isolate               Runtime isolate.
         * @param exports               Addon exports.
         */
        explicit JSON(Runtime::Isolate* isolate, Dylib::Exports& exports);

       private:
        //  PRIVATE METHODS  //

#define X(N, ...) static Value::Any m_##N(Runtime::Isolate* isolate, const Function::Arguments& args);
        CRATE_XX_JSON_METHODS(X)
#undef X
    };

}  // namespace Talos::Package

#endif
