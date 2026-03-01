#ifndef _FORGE_RUNTIME_ISOLATE_HPP
#define _FORGE_RUNTIME_ISOLATE_HPP

/// Forge Modules
#include "forge/async/thenable.hpp"
#include "forge/diagnostic/traits.hpp"
#include "forge/forward/async.hpp"
#include "forge/forward/engine.hpp"
#include "forge/forward/module.hpp"
#include "forge/globals/roots.hpp"
#include "forge/handle/list.hpp"
#include "forge/handle/local.hpp"
#include "forge/handle/scope.hpp"
#include "forge/iterable/list.hpp"
#include "forge/object/exception.hpp"
#include "forge/resource/path.hpp"
#include "forge/resource/trace.hpp"
#include "forge/runtime/allocator.hpp"
#include "forge/runtime/options.hpp"

namespace Forge::Runtime {

    /// @brief Runtime Thread Isolate.
    class $_ABSTRACT Isolate {
        //  TYPEDEFS  //

        /// @brief Allow interpreter frames internal access.
        friend struct Engine::Frame;

        /// @brief Allow handlers internal access.
        template <std::derived_from<Value::Any> T>
        friend class Handle::Local;

       protected:
        //  PROPERTIES  //

        /// @brief Runtime service instance.
        XI::Container* m_services;

        /// @brief Currently bound interpreter frame.
        Engine::Frame* m_frame = nullptr;

        /// @brief Bound data value to assign.
        Value::Any m_data = Value::Void();

        /// @brief Currently bound exception value.
        Value::Any m_exception = Value::Void();

        /// @brief Currently attached value handles.
        Handle::List m_handles = Handle::List();

        /// @brief The underlying stack frame buffer.
        Allocator m_allocator = Allocator();

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a runtime isolate.
         * @param services              Services container.
         * @param data                  Bound data value.
         */
        explicit Isolate();
        explicit Isolate(XI::Container* services);
        explicit Isolate(XI::Container* services, const Value::Any& data);

        /// @brief Virtual abstract destructor.
        virtual ~Isolate() = default;

        //  PUBLIC METHODS  //

        /// @brief Gets the current interpreter frame.
        inline constexpr Engine::Frame* frame() const noexcept { return m_frame; }

        /// @brief Current exception value (usually "void").
        inline constexpr Value::Any exception() const noexcept { return m_exception; }

        /// @brief Constructs a local handle scoping.
        inline constexpr Handle::Scope scope() noexcept { return Handle::Scope(this); }

        /// @brief Gets the underlying runtime options.
        inline constexpr const Options* options() const noexcept { return service<Options>(); }

        /// @brief Gets the assocated runtime allocator.
        inline constexpr Allocator* allocator() noexcept { return &m_allocator; }

        /// @brief Gets the underlying thread instance (allows mocking).
        virtual inline constexpr Async::Thread* thread() const noexcept { return nullptr; }

        /// @brief Gets a service from the runtime.
        template <std::derived_from<XI::Shared> T>
        inline constexpr T* service() const noexcept {
            return $_ASSERT(m_services->exists<T>()), m_services->get<T>();
        }

        /// @brief Gets a unique service from the runtime.
        template <std::derived_from<XI::Unique> T>
        inline constexpr $::Ptr::Unique<T> service() const noexcept {
            return m_services->get<T>();
        }

        /// @brief Handles getting the underlying services container.
        template <std::derived_from<XI::Container> T>
        inline constexpr XI::Container* service() const noexcept {
            return m_services;  // get the base container now
        }

        /// @brief Cancels an isolates execution.
        Value::Any interrupt();

        /// @brief Gets a formatted backtrace value.
        std::vector<Resource::Trace> backtrace();

        /**
         * @brief Handles yield isolate roots.
         * @param yield                     Yield handler.
         */
        void roots(const Globals::Each& yield);

        /**
         * @brief Gets the available exports.
         * @param resource                  Resource to resolve.
         */
        Engine::Exports* exports(const $::URI::View& resource);

        /**
         * @brief Gets the available exports.
         * @param script                    Script value.
         * @param hint                      Directory hint.
         */
        Engine::Exports* exports(const $::String::View& script);
        Engine::Exports* exports(const $::String::View& script, const $::Filesystem::Path& hint);

        /**
         * @brief Handles retrieving a global.
         * @param symbol                    Symbol to retrieve.
         */
        Value::Any global(Value::Symbol symbol);

        /**
         * @brief Gets the intern associated with a symbol.
         * @param symbol                    Symbol to retrieve.
         */
        const String::Intern* intern(Value::Symbol symbol);

        /**
         * @brief Handles spawning callbacks/futures.
         * @param target                    Target to spawn.
         * @param args                      Arguments to bind.
         * @param trace                     Optional trace.
         */
        Async::Result spawn(Value::Any target);
        Async::Result spawn(Value::Any target, const Resource::Trace& trace);
        Async::Result spawn(Value::Any target, Function::Arguments&& args);
        Async::Result spawn(Value::Any target, Function::Arguments&& args, const Resource::Trace& trace);

        /**
         * @brief Handles calling functions.
         * @param target                    Target to call.
         * @param args                      Arguments to bind.
         */
        Value::Any invoke(Value::Any target);
        Value::Any invoke(Value::Any target, const Function::Arguments& args);

        /**
         * @brief Allows binding function receivers.
         * @param callback                  Function to bind.
         * @param receiver                  Callback receiver.
         */
        Function::Dynamic bind(const Function::Dynamic& callback, Value::Any receiver);

        /**
         * @brief Handles resolving runtime paths.
         * @param script                    Script value.
         * @param hint                      Directory hint.
         */
        Resource::Result resolve(const $::String::View& script) const;
        Resource::Result resolve(const $::String::View& script, const $::Filesystem::Path& hint) const;

        /**
         * @brief Handles importing resources.
         * @param resource                  Resource to import.
         * @param hint                      Optional directory hint.
         * @param trace                     Optional resource trace.
         */
        Value::Any import(const $::URI::View& resource);
        Value::Any import(const $::URI::View& resource, const Resource::Trace& trace);
        Value::Any import(const $::String::View& script, const Resource::Trace& trace);
        Value::Any import(const $::String::View& script, const $::Filesystem::Path& hint);
        Value::Any import(const $::String::View& script, const $::Filesystem::Path& hint, const Resource::Trace& trace);

        /**
         * @brief Handles throwing an exception.
         * @param exception                 Exception to throw.
         */
        inline Value::Any panic(Object::Exception exception) {
            if (m_exception != exception) m_exception = exception;
            return Value::Failure();  // force a failure here
        }

        /**
         * @brief Handles throwing reasoned exceptions.
         * @param reason                    Reason to throw.
         */
        inline Value::Any panic(Value::Any reason) {
            if (reason.is<Value::Void>()) return panic(6000001);  // the baseline exception
            else if (reason.is<String::Dynamic>()) return panic(reason.as<String::Dynamic>());
            else if (reason.is<Object::Exception>()) return panic(reason.as<Object::Exception>());
            else return panic($::Convert::stringify<Value::Any>(reason));  // otherwise stringify
        }

        /**
         * @brief Handles throwing an exception.
         * @param message                   Message to format.
         * @param args                      Exception arguments.
         */
        template <class... As>
        inline Value::Any panic(const $::String::View& message, As&&... args) {
            return panic(create<Object::Exception>(fmt::format(fmt::runtime(message), std::forward<As>(args)...)));
        }

        /**
         * @brief Handles throwing an exception.
         * @param code                      Diagnostic code.
         * @param args                      Exception arguments.
         */
        template <class... As>
        inline Value::Any panic(Diagnostic::Code code, As&&... args) {
            auto category = Diagnostic::Traits::category(code);
            auto message = Diagnostic::Traits::format(code, std::forward<As>(args)...);
            return panic(create<Object::Exception>(category, message));
        }

        /**
         * @brief Handles throwing a basic exception.
         * @param args                      Exceptions arguments.
         */
        template <class... As>
        inline Value::Any panic(As&&... args) {
            return panic(create<Object::Exception>(std::forward<As>(args)...));
        }

        /**
         * @brief Handles constructing heap values.
         * @param args                      Arguments to bind.
         */
        template <std::derived_from<Value::Any> T, class... As>
        inline T create(As&&... args) {
            return m_allocator.create<T, As...>(std::forward<As>(args)...);
        }
    };

}  // namespace Forge::Runtime

//  SPECIALIZATIONS  //

template <std::derived_from<Forge::Value::Any> T>
Forge::Handle::Local<T>::Local(Scope* scope) :
    m_isolate(scope->m_isolate), m_next(m_isolate->m_handles.push(m_reference())) {}

template <std::derived_from<Forge::Value::Any> T>
Forge::Handle::Local<T>::Local(Scope* scope, Value::Any value) :
    m_isolate(scope->m_isolate), m_next(m_isolate->m_handles.push(m_reference())), m_value(value) {
    if constexpr (!std::same_as<T, Value::Any>) $_ASSERT(value.is<T>());
}

template <std::derived_from<Forge::Value::Any> T>
Forge::Handle::Local<T>::~Local() {
    $_ASSERT(m_isolate->m_handles.head() == m_reference(), "Mismatched locals head");
    m_isolate->m_handles.pop(m_next);  // pop the top-most head now as necessary
}

#endif
