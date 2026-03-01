#ifndef _CRATES_PACKAGE_TEST_HPP
#define _CRATES_PACKAGE_TEST_HPP

/// Vendor Modules
#include <xtest/xtest.hpp>

/// Forge Modules
#include <forge/async/thenable.hpp>
#include <forge/dylib/registry.hpp>
#include <forge/engine/frame.hpp>
#include <forge/forward/testing.hpp>

//  X-MACROS  //

#define CRATE_XX_TEST_METHODS(X) \
    X(case)                      \
    X(skip)                      \
    X(todo)                      \
    X(bench)                     \
    X(suite)

//  NAMESPACES  //

namespace Forge::Package {

    /// @brief Testing Package Addon.
    struct Test : public Dylib::Proxy<"Test"> {
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a testing library.
         * @param isolate               Runtime isolate.
         * @param exports               Addon exports.
         */
        explicit Test(Runtime::Isolate* isolate, Dylib::Exports& exports);

       private:
        //  PRIVATE METHODS  //

#define X(N, ...) static Value::Any m_##N(Runtime::Isolate* isolate, const Function::Arguments& args);
        CRATE_XX_TEST_METHODS(X)
#undef X

        /**
         * @brief Handles validating testing is enabled.
         * @param isolate               Runtime isolate.
         */
        static bool m_enabled(Runtime::Isolate* isolate);

        /**
         * @brief Handles registering tests.
         * @param isolate                Runtime isolate.
         * @param args                   Function arguments.
         */
        static Testing::Case* m_register(Runtime::Isolate* isolate, const Function::Arguments& args);

        /**
         * @brief Resolves testing callbacks.
         * @param callback              Callback to bind.
         * @param group                 Optional target group.
         */
        static Testing::Callback m_callback(const Function::Dynamic& callback);
        static Testing::Callback m_callback(const Function::Dynamic& callback, Testing::Group* group);

        /**
         * @brief Handles running testing callbacks.
         * @param runner                Testing runner.
         * @param callback              Callback to execute.
         */
        static void m_callback(Testing::Runner* runner, const Function::Dynamic& callback);

        /**
         * @brief Handles racing a callback.
         * @param runner                Testing runner.
         * @param callback              Callback to execute.
         */
        static Async::Result m_race(Testing::Runner* runner, const Function::Dynamic& callback);

        /**
         * @brief Converts an isolate into a location.
         * @param isolate               Runtime isolate.
         */
        static XT::Location m_location(Runtime::Isolate* isolate);
        static XT::Location m_location(const Engine::Frame* frame);
        static XT::Location m_location(const Resource::Trace& trace);
    };

}  // namespace Forge::Package

#endif
