#ifndef _CRATES_PACKAGE_ASSERT_HPP
#define _CRATES_PACKAGE_ASSERT_HPP

/// Talos Modules
#include <talos/diagnostic/traits.hpp>
#include <talos/dylib/registry.hpp>
#include <talos/runtime/isolate.hpp>

//  X-MACROS  //

#define CRATE_XX_ASSERT_METHODS(X) \
    X(fail)                        \
    X(okay)                        \
    X(truthy)                      \
    X(falsey)                      \
    X(exists)                      \
    X(panics)                      \
    X(equals)                      \
    X(differs)

//  NAMESPACES  //

namespace Talos::Package {

    /// @brief Assertion Package Addon.
    struct Assert : public Dylib::Proxy<"Assert"> {
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an assertion library.
         * @param isolate               Runtime isolate.
         * @param exports               Addon exports.
         */
        explicit Assert(Runtime::Isolate* isolate, Dylib::Exports& exports);

       private:
        //  PRIVATE METHODS  //

#define X(N, ...) static Value::Any m_##N(Runtime::Isolate* isolate, const Function::Arguments& args);
        CRATE_XX_ASSERT_METHODS(X)
#undef X

        /**
         * @brief Handles testing assertions.
         * @param isolate               Runtime isolate.
         * @param args                  Function arguments.
         * @param state                 Assertion state.
         * @param method                Method to check.
         */
        static Value::Any m_test(
            Runtime::Isolate* isolate, const Function::Arguments& args, bool state, const $::String::View& method);

        /**
         * @brief Handles throwing an exception.
         * @param isolate               Runtime isolate.
         * @param exception             Exception to throw.
         */
        static Value::Any m_panic(Runtime::Isolate* isolate, Object::Exception exception);

        /**
         * @brief Handles throwing an exception.
         * @param isolate               Runtime isolate.
         * @param code                  Diagnostic code.
         * @param args                  Exception arguments.
         */
        template <class... As>
        static inline Value::Any m_panic(Runtime::Isolate* isolate, Diagnostic::Code code, As&&... args) {
            auto category = Diagnostic::Traits::category(code);  // prepare the items
            auto message = Diagnostic::Traits::format(code, std::forward<As>(args)...);
            return m_panic(isolate, isolate->create<Object::Exception>(category, message));
        }
    };

}  // namespace Talos::Package

#endif
