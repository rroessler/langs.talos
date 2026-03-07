#ifndef _TALOS_MACHINE_SERVICE_HPP
#define _TALOS_MACHINE_SERVICE_HPP

/// Talos Modules
#include "talos/forward/machine.hpp"
#include "talos/function/dynamic.hpp"

namespace Talos::Machine {

    /// @brief Machine Code Service.
    class Service : public XI::Define<Service, XI::Shared> {
        //  PROPERTIES  //

        /// @brief Compilation mutex.
        mutable $::Mutex::Auto m_mutex;

        /// @brief Available services container.
        XI::Container* m_services = nullptr;

        /// @brief The underlying machine-code context.
        XASM::Runtime::Context m_context = {};

        /// @brief Currently bound callees.
        $::Set<$::Ptr::Unique<Info>> m_callees = {};

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a machine-code service.
        explicit Service();
        explicit Service(XI::Container* services);

        //  PUBLIC METHODS  //

        /**
         * @brief Validates a closure can be compiled to machine-code.
         * @param closure               Closure function.
         */
        bool verify(Function::Closure closure) const noexcept;
        bool verify(const Function::Info* info) const noexcept;

        /**
         * @brief Attempts compiling a closure to machine-code.
         * @param isolate               Runtime isolate.
         * @param closure               Closure function.
         */
        Function::Dynamic compile(Runtime::Isolate* isolate, Function::Closure closure);
        Function::Dynamic compile(Runtime::Isolate* isolate, const Function::Info* info);
        Function::Dynamic compile(Runtime::Isolate* isolate, const Function::Info* info, Value::Any context);

       private:
        //  PRIVATE METHODS  //

        /// @brief Handles dumping the current logging outputs.
        void m_dump(const Function::Info* info) const noexcept;
    };

}  // namespace Talos::Machine

#endif
