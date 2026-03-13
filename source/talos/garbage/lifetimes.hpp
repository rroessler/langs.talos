#ifndef _TALOS_GARBAGE_LIFETIMES_HPP
#define _TALOS_GARBAGE_LIFETIMES_HPP

/// Talos Modules
#include "talos/forward/engine.hpp"
#include "talos/forward/garbage.hpp"
#include "talos/object/common.hpp"

/**
 * A lifetimes instance handles opening/closing disposable value stacks. As such,
 * it coordinates explicit resource management. Internally, disposables are contained
 * based on their associated `Engine::Frame`, and as such are disposed when a frame
 * goes out of scope (since they are always locally scoped). Since each disposable value
 * is "theoretically" contained outside of the lifetimes container, each value contained
 * here do not need to be manually managed (eg: via the `Globals::Roots` instance).
 */

namespace Talos::Garbage {

    /// @brief Handles Disposable Lifetimes.
    class Lifetimes : public XI::Define<Lifetimes, XI::Unique> {
        //  TYPEDEFS  //

        /// @brief Available scoping of values.
        using Scope = std::vector<Value::Any>;

        /// @brief Available stacks to close.
        using Stack = std::vector<Scope>;

        //  PROPERTIES  //

        /// @brief Prepare the mapping.
        $::Map<const Engine::Frame*, Stack> m_stacks = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs diposable lifetimes.
        explicit Lifetimes() = default;

        //  PUBLIC METHODS  //

        /**
         * @brief Attempts opening to a depth.
         * @param isolate               Runtime isolate.
         * @param depth                 Opening depth.
         */
        void open(Runtime::Isolate* isolate);
        void open(Runtime::Isolate* isolate, size_t depth);

        /**
         * @brief Closes to a required depth.
         * @param isolate               Runtime isolate.
         * @param depth                 Closing depth.
         */
        bool close(Runtime::Isolate* isolate);
        bool close(Runtime::Isolate* isolate, size_t depth);

        /**
         * @brief Value to defer for disposal.
         * @param isolate               Runtime isolate.
         * @param value                 Value to defer.
         */
        void defer(Runtime::Isolate* isolate, Value::Any value);

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles disposing a set of values.
         * @param isolate               Runtime isolate.
         * @param values                Values to dispose.
         */
        bool m_dispose(Runtime::Isolate* isolate, Scope& values);
        bool m_dispose(Runtime::Isolate* isolate, Value::Any value);

        /**
         * @brief Checks if an original exception should be suppressed.
         * @param isolate               Runtime isolate.
         * @param exception             Exception value.
         */
        void m_suppress(Runtime::Isolate* isolate, Value::Any exception);
        void m_suppress(Runtime::Isolate* isolate, Object::Exception exception);
    };

}  // namespace Talos::Garbage

#endif
