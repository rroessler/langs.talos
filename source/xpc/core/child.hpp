#ifndef _XPC_CORE_CHILD_HPP
#define _XPC_CORE_CHILD_HPP

/// XPC Modules
#include "xpc/core/identifier.hpp"
#include "xpc/pipe/duplex.hpp"
#include "xpc/shell/types.hpp"
#include "xtdlib/string/buffer.hpp"

namespace XPC::Core {

    /// @brief The available symbolic signals.
    using Signal = XSIO::Signal::Symbolic;

    /// @brief Child Process Container.
    class Child {
        //  PROPERTIES  //

        /// @brief The underlying process identifier.
        Identifier m_pid = 0;

        /// @brief Prepare the current exit-code.
        int32_t m_errc = INT32_MIN;

        /// @brief Standard input pipe.
        Pipe::Duplex m_stdin = {};

        /// @brief Standard output pipe.
        Pipe::Duplex m_stdout = {};

        /// @brief Standard error pipe.
        Pipe::Duplex m_stderr = {};

#if $_PLATFORM_WINDOWS
        /// @brief Process information (windows).
        PROCESS_INFORMATION m_info = {};
#endif

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs an empty/invalid sub-process.
        constexpr Child() = default;

        /**
         * @brief Handles initializing a child process.
         * @param options                   Process options.
         */
        constexpr Child(const Shell::Options& options) { m_initialize(options); }
        constexpr Child(const Shell::Builder& builder) : Child(builder.merge()) {}

        /**
         * @brief Handles initializing a child process.
         * @param command                   Command name.
         * @param options                   Process options.
         */
        constexpr Child(const $::String::Buffer& command, const Shell::Options& options = {}) :
            Child(Shell::Builder(command, options)) {}

        /// @brief Do not allow copy-construction.
        constexpr Child(const Child&) = delete;

        /// @brief Do allow move-construction.
        constexpr Child(Child&& other) { *this = std::move(other); }

        /// @brief Handles terminating the child-process.
        constexpr ~Child() { m_destroy(); }

        //  OPERATOR METHODS  //

        inline constexpr Child& operator=(const Child&) = delete;
        inline constexpr Child& operator=(Child&& other) {
            // move the underlying error-code and pid
            m_pid = other.m_pid, other.m_pid = 0;
            m_errc = other.m_errc, other.m_errc = INT32_MIN;

#if $_PLATFORM_WINDOWS
            // move the process-information
            m_info = other.m_info, other.m_info = {};
#endif

            // move all the underlying pipes
            m_stdin = std::move(other.m_stdin);
            m_stdout = std::move(other.m_stdout);
            m_stderr = std::move(other.m_stderr);

            // return the resulting reference
            return *this;
        }

        //  PUBLIC METHODS  //

        /// @brief Gets the process identifier.
        inline constexpr const Identifier& pid() const noexcept { return m_pid; }
        inline constexpr Identifier ppid() const noexcept { return m_ppid(); }

        /// @brief Gets the standard input pipe.
        inline constexpr Pipe::Writer cin() const noexcept { return pin()->writable(); }
        inline constexpr const Pipe::Simplex* pin() const noexcept { return m_stdin.output(); }

        /// @brief Gets the standard output pipe.
        inline constexpr Pipe::Reader cout() const noexcept { return pout()->readable(); }
        inline constexpr const Pipe::Simplex* pout() const noexcept { return m_stdout.input(); }

        /// @brief Gets the standard error pipe.
        inline constexpr Pipe::Reader cerr() const noexcept { return pout()->readable(); }
        inline constexpr const Pipe::Simplex* perr() const noexcept { return m_stderr.input(); }

        /**
         * @brief Emits a signal to the child-process.
         * @param signal                    Signal to send.
         */
        inline constexpr bool kill(const XSIO::Signal::Code& signal = Signal::KILL) { return m_signal(signal); }

        /// @brief Polls the process to check if it finished.
        inline constexpr bool poll() { return m_poll(); }

        /**
         * @brief Handles waiting for a child-process to complete.
         * @param duration                  Wait option.
         */
        inline constexpr int32_t wait() { return m_wait(); }
        inline constexpr int32_t wait(const XSIO::Timer::Ticks& duration) { return m_wait(duration); }
        inline constexpr int32_t wait(const XSIO::Timer::Point& timestamp) { return m_wait(timestamp); }

       private:
        //  PRIVATE METHODS  //

        /// @brief Polls the current child-process status.
        bool m_poll();

        /// @brief Handles destroying the underlying process.
        void m_destroy();

        /// @brief Gets the parent process identifier.
        Identifier m_ppid() const;

        /**
         * @brief Handles initializing the child-process.
         * @param command                   Shell command.
         * @param options                   Process options.
         */
        void m_initialize(const Shell::Options& options);
        void m_initialize(const $::String::Buffer& command, const Shell::Options& options);

        /**
         * @brief Emits a signal to a child-process.
         * @param signal                    Signal to send.
         */
        bool m_signal(const XSIO::Signal::Code& signal);

        /**
         * @brief Handles waiting for a child-process to complete.
         * @param duration                  Wait option.
         */
        int32_t m_wait();
        int32_t m_wait(const XSIO::Timer::Ticks& duration);
        int32_t m_wait(const XSIO::Timer::Point& timestamp);
    };

}  // namespace XPC::Core

#endif
