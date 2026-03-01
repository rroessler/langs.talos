#ifndef _XPC_PIPE_SIMPLEX_HPP
#define _XPC_PIPE_SIMPLEX_HPP

/// XPC Modules
#include "xpc/pipe/direct.hpp"
#include "xpc/pipe/reader.hpp"
#include "xpc/pipe/writer.hpp"

namespace XPC::Pipe {

    /// @brief Simplex Pipe Containers.
    class Simplex {
        //  PROPERTIES  //

        /// @brief The native handle.
        Handle m_handle = Invalid();

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs an invalid pipe.
        constexpr Simplex() = default;

        /**
         * @brief Constructs a unique pipe.
         * @param handle                Pipe handle.
         */
        constexpr Simplex(Handle handle) : m_handle(handle) {}

        /// @brief Do not allow copying pipes.
        constexpr Simplex(const Simplex&) = delete;

        /// @brief Allow moving pipes.
        constexpr Simplex(Simplex&& other) : m_handle(other.detach()) {}

        /// @brief Handls safely destorying pipes.
        constexpr ~Simplex() { close(); }

        //  OPERATOR METHODS  //

        inline constexpr Simplex& operator=(const Simplex&) = delete;
        inline constexpr Simplex& operator=(Simplex&& other) { return m_handle = other.detach(), *this; }

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying pipe handle.
        inline constexpr Handle handle() const noexcept { return m_handle; }

        /// @brief Denotes if the pipe is currently invalid.
        inline constexpr bool invalid() const noexcept { return m_handle == Invalid(); }

        /// @brief Gets the available reader handler.
        inline constexpr Reader readable() const noexcept { return Reader(&m_handle); }

        /// @brief Gets the available writer handler.
        inline constexpr Writer writable() const noexcept { return Writer(&m_handle); }

        /// @brief Handles closing the pipe.
        inline constexpr bool close() noexcept { return m_close(); }

        /// @brief Forcibly detaches the bound handle.
        inline constexpr Handle detach() noexcept {
            auto ref = m_handle;  // clone
            return m_handle = Invalid(), ref;
        }

        /// @brief Sets the current inheritance flag.
        inline constexpr bool atomic(bool atomic) noexcept { return m_inherits(atomic); }

        /// @brief Sets the current blocking flag.
        inline constexpr bool blocking(bool state) noexcept { return m_blocking(state); }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Closes a given pipe value.
         * @param handle                Handle to close.
         */
        bool m_close() noexcept;

        /**
         * @brief Sets the inheritable state.
         * @param atomic                Atomic flag.
         */
        bool m_inherits(bool atomic) noexcept;

        /**
         * @brief Sets the blocking state.
         * @param atomic                Atomic flag.
         */
        bool m_blocking(bool state) noexcept;
    };

}  // namespace XPC::Pipe

#endif
