#ifndef _CRATES_PACKAGE_GARBAGE_HPP
#define _CRATES_PACKAGE_GARBAGE_HPP

/// Talos Modules
#include <talos/dylib/registry.hpp>
#include <talos/garbage/service.hpp>

//  X-MACROS  //

#define CRATE_XX_GARBAGE_METHODS(X) \
    X(cycles)                       \
    X(collect)

//  NAMESPACES  //

namespace Talos::Package {

    /// @brief Garbage Package Addon.
    class Garbage : public Dylib::Proxy<"Garbage"> {
        //  TYPEDEFS  //

        /// @brief Available service typing.
        using Service = ::Talos::Garbage::Service;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an assertion library.
         * @param isolate               Runtime isolate.
         * @param exports               Addon exports.
         */
        explicit Garbage(Runtime::Isolate* isolate, Dylib::Exports& exports);

       private:
        //  PRIVATE METHODS  //

#define X(N, ...) static Value::Any m_##N(Runtime::Isolate* isolate, const Function::Arguments& args);
        CRATE_XX_GARBAGE_METHODS(X)
#undef X
    };

}  // namespace Talos::Package

#endif
