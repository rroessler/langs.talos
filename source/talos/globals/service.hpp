#ifndef _TALOS_GLOBALS_SERVICE_HPP
#define _TALOS_GLOBALS_SERVICE_HPP

/// Talos Modules
#include "talos/builtins/proxy.hpp"
#include "talos/globals/roots.hpp"
#include "talos/object/class.hpp"
#include "talos/value/symbol.hpp"

//  MACROS  //

#define TALOS_MM_GLOBALS_NATIVE(I, N, C, ...)                                     \
    I->service<::Talos::Globals::Service>()->internal<::Talos::Function::Native>( \
        I, N, [](::Talos::Runtime::Isolate* isolate) { return isolate->create<::Talos::Function::Native>(C, N); })

//  NAMESPACES  //

namespace Talos::Globals {

    /// @brief Builtin Global Values.
    class Service : public XI::Define<Service, XI::Shared> {
        //  PROPERTIES  //

        /// @brief Ensure values can only be accessed one-at-a-time.
        mutable $::Mutex::Shared m_mutex;

        /// @brief Currently instantiated values (eg: runtime-values).
        $::Map<Value::Symbol, Value::Any> m_values = {};

        /// @brief Available internal values (eg: native-functions).
        $::Map<Value::Symbol, Value::Any> m_internal = {};

        /// @brief Preloaded factories for use.
        $::Map<Value::Symbol, Factory> m_factories = {};

        /// @brief Explicitly available global roots.
        $::Ptr::Unique<Roots> m_roots = $::New().unique<Roots>();

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a set of global values.
        explicit Service();

        //  PUBLIC METHODS  //

        /// @brief Gets all the available runtime roots.
        inline constexpr Roots* roots() const noexcept { return m_roots.get(); }

        /**
         * @brief Denotes if a symbol exists.
         * @param symbol                Symbol to query.
         */
        inline constexpr bool has(Value::Symbol symbol) const noexcept {
            return m_values.contains(symbol) || m_factories.contains(symbol);
        }

        /**
         * @brief Explicitly casts a global to a type.
         * @tparam T                        Type to cast.
         * @param thread                    Thread isolate.
         * @param symbol                    Global symbol.
         */
        template <std::derived_from<Value::Any> T>
        inline constexpr T get(Runtime::Isolate* isolate, Value::Symbol symbol) {
            return get(isolate, symbol).as<T>();
        }

        /**
         * @brief Allow getting cached persitent globals.
         * @param isolate               Thread isolate.
         * @param symbol                Global symbol.
         * @param factory               Factory to use.
         */
        template <std::derived_from<Value::Any> T>
        inline constexpr T internal(Runtime::Isolate* isolate, Value::Symbol symbol, Factory&& factory) {
            return internal(isolate, symbol, std::move(factory)).as<T>();
        }

        /**
         * @brief Attempts getting a global prototype.
         * @tparam T                    Type of prototype.
         * @param isolate               Thread isolate.
         */
        template <std::derived_from<Value::Any> T>
        inline constexpr Object::Class prototype(Runtime::Isolate* isolate) {
            return get<Object::Class>(isolate, Builtins::Proxy<T>::name());
        }

        /**
         * @brief Allow getting cached persitent globals.
         * @param isolate               Thread isolate.
         * @param symbol                Global symbol.
         * @param factory               Factory to use.
         */
        inline constexpr Value::Any internal(Runtime::Isolate* isolate, Value::Symbol symbol, Factory&& factory) {
            if (m_internal.contains(symbol)) return m_internal.at(symbol);
            $_UNUSED $_AUTO = $::Lock::guard(m_mutex);  // ensure thread-safe
            return m_internal.emplace(symbol, factory(isolate)).first->second;
        }

        /**
         * @brief Ensures that we can set a global variable.
         * @param isolate               Thread isolate.
         * @param symbol                Global symbol.
         */
        inline constexpr Value::Any get(Runtime::Isolate* isolate, Value::Symbol symbol) {
            if (m_values.contains(symbol)) return m_values.at(symbol);
            $_UNUSED $_AUTO = $::Lock::guard(m_mutex);  // ensure thread-safe before continuing
            return m_values.emplace(symbol, m_factories.at(symbol)(isolate)).first->second;
        }
    };

}  // namespace Talos::Globals

#endif
