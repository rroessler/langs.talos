#ifndef _XSIO_TASK_EXECUTOR_HPP
#define _XSIO_TASK_EXECUTOR_HPP

/// XSIO Modules
#include "xsio/forward/task.hpp"
#include "xsio/forward/virtual.hpp"

namespace XSIO::Task {

    /// @brief Executor Abstraction.
    class $_ABSTRACT Executor : public $::RTTI::Dynamic {
        //  TYPEDEFS  //

        /// @brief Allow threads internal access.
        friend class Virtual::Thread;

       protected:
        //  PROPERTIES  //

        /// @brief Allow reference to the attached thread instance.
        Virtual::Thread* m_thread = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Default constructor.
        explicit Executor() = default;

        /// @brief Virtual abstract destructor.
        virtual ~Executor() = default;

        //  PUBLIC METHODS  //

        inline constexpr void detach() { m_thread = nullptr; }
        inline constexpr Virtual::Thread* thread() const noexcept { return m_thread; }
        inline constexpr bool running() const noexcept { return m_thread != nullptr; }

       protected:
        //  PRIVATE METHODS  //

        /// @brief Handles executing the task now.
        virtual void m_execute() = 0;
    };

    /// @brief Executor Task Abstraction.
    template <class T>
    using Abstract = $::RTTI::Extends<T, Executor>;

}  // namespace XSIO::Task

#endif
