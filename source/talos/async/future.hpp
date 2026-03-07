#ifndef _TALOS_ASYNC_FUTURE_HPP
#define _TALOS_ASYNC_FUTURE_HPP

/// Talos Modules
#include "talos/async/thenable.hpp"
#include "talos/function/dynamic.hpp"
#include "talos/object/abstract.hpp"

namespace Talos {

    /// @brief Future Attributes.
    template <>
    struct Object::Attributes<Async::Future> {
        //  PROPERTIES  //

        /// @brief Callback handler.
        Function::Dynamic callback = {};

        /// @brief Bound arguments.
        Function::Arguments arguments = {};

        /// @brief The bound future worker.
        Runtime::Isolate* worker = nullptr;

        /// @brief The default result value.
        $::Ptr::Unique<Async::Thenable> thenable = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs an anonymous future.
        explicit Attributes() : thenable($::New().unique<Async::Thenable>()) {}

        /**
         * @brief Constructs future attributes.
         * @param callee                Calling isolate.
         * @param callback              Callback to bind.
         * @param args                  Arguments to bind.
         */
        explicit Attributes(Runtime::Isolate* callee, Function::Dynamic callback);
        explicit Attributes(Runtime::Isolate* callee, Function::Dynamic callback, Function::Arguments&& args);
        explicit Attributes(Runtime::Isolate* callee, Function::Dynamic callback, const Function::Arguments& args);

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles intializing a future.
         * @param callee                 Calling isolate.
         */
        void m_initialize(Runtime::Isolate* callee);
    };

    /// @brief Future Interface.
    struct Async::Future : public Object::Abstract<Async::Future> {
        //  TYPEDEFS  //

        /// @brief Allow async-workers internal access.
        friend class Worker;

        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructor.
        using Abstract::Abstract;

        //  PUBLIC METHODS  //

        inline constexpr bool pending() const noexcept { return m_attrs()->thenable->pending(); }
        inline constexpr bool unassigned() const noexcept { return m_attrs()->callback.traits().null(); }
        inline constexpr XSIO::Task::Status status() const noexcept { return m_attrs()->thenable->status(); }

        inline constexpr Async::Thenable* thenable() const noexcept { return m_attrs()->thenable.get(); }
        inline constexpr Function::Dynamic& callback() const noexcept { return m_attrs()->callback; }
        inline constexpr Function::Arguments& arguments() const noexcept { return m_attrs()->arguments; }

        /**
         * @brief Handles waiting for a future to complete.
         * @param thread                    Virtual thread.
         */
        Result await(Thread* thread) const noexcept;
        Value::Any await(Runtime::Isolate* isolate) const noexcept;

        /**
         * @brief Waits for a future to complete within a duration.
         * @param thread                    Virtual thread.
         * @param duration                  Timeout duration.
         */
        Result timeout(Thread* thread, const $::Chrono::Duration& duration) const noexcept;
        Value::Any timeout(Runtime::Isolate* isolate, const $::Chrono::Duration& duration) const noexcept;

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handlers yielding futures safely.
         * @param self                          Future instance.
         * @param yield                         Yield callback.
         */
        static void m_yield(const Future& self, const Globals::Each& yield);

        /**
         * @brief Instantiates a timeout instance.
         * @param duration                  Timeout duration.
         */
        Timeout m_timeout(const $::Chrono::Duration& duration) const noexcept;
    };

}  // namespace Talos

#endif
