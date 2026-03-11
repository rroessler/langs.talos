#ifndef _CRATES_PACKAGE_UUID_HPP
#define _CRATES_PACKAGE_UUID_HPP

/// Talos Modules
#include <talos/dylib/registry.hpp>
#include <talos/runtime/isolate.hpp>

/// Assert Modules
#include <talos/builtins/_inline/assert.ipp>

//  X-MACROS  //

#define CRATE_XX_UUID_METHODS(X) \
    X(V1)                        \
    X(V3)                        \
    X(V4)                        \
    X(V5)                        \
    X(V6)                        \
    X(V7)

//  NAMESPACES  //

namespace Talos::Package {

    /// @brief UUID Package Addon.
    struct UUID : public Dylib::Proxy<"uuid"> {
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a "uuid" library.
         * @param isolate               Runtime isolate.
         * @param exports               Addon exports.
         */
        explicit UUID(Runtime::Isolate* isolate, Dylib::Exports& exports);

       private:
        //  PRIVATE METHODS  //

#define X(N, ...) static Value::Any m_##N(Runtime::Isolate* isolate, const Function::Arguments& args);
        CRATE_XX_UUID_METHODS(X)
#undef X

        /**
         * @brief Handles generating UUID values.
         * @param isolate               Runtime isolate.
         * @param callback              Generator callback.
         * @param args                  Generator arguments.
         */
        template <class V, class... As>
        static inline constexpr Value::Any m_generate(Runtime::Isolate* isolate, V callback, As&&... args) {
            char buffer[muuid::uuid::char_length] = {};
            callback(std::forward<As>(args)...).to_chars(buffer);  // resolve now
            auto view = $::String::View(buffer, muuid::uuid::char_length);
            return String::Dynamic(isolate, view);  // and construct result
        }

        /**
         * @brief Handles validating namespace UUIDs.
         * @param isolate               Runtime isolate.
         * @param args                  Incoming arguments.
         * @param callback              Generator callback.
         */
        template <class V>
        static inline constexpr Value::Any m_namespace(
            Runtime::Isolate* isolate, const Function::Arguments& args, V callback) {
            // attempt resolving a suitable seed value now
            auto seed = args.at(0, m_V4(isolate, args));

            // attempt resolving a suitable name to be used
            auto name = args.at(1, String::Dynamic());

            // ensure our incoming values are both valid
            TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, seed);
            TALOS_MM_ASSERT_TYPEOF(isolate, String::Dynamic, name);

            auto local_scope = isolate->scope();  // prepare scoping
            auto local_seed = local_scope(seed.as<String::Dynamic>());
            auto local_name = local_scope(name.as<String::Dynamic>());

            // get the namespace to actually be used now
            auto ns = muuid::uuid().from_chars(local_seed->view());

            // ensure the namespace resolved to a valid "uuid"
            if (!ns.has_value()) return isolate->panic(6000000, "Invalid seed namespace");

            // and attempt resolving our namespaced instance
            return m_generate(isolate, callback, *ns, local_name->view());
        }
    };

}  // namespace Talos::Package

#endif
