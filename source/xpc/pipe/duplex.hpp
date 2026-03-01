#ifndef _XPC_PIPE_DUPLEX_HPP
#define _XPC_PIPE_DUPLEX_HPP

/// XPC Modules
#include "xpc/pipe/simplex.hpp"

namespace XPC::Pipe {

    /// @brief Basic Pipe Atomic Flags.
    enum class Atomic : bool {
        INHERIT = true,   // do not close after
        DEFAULT = false,  // close after execute
        CLOEXEC = false,  // close after execute
    };

    /// @brief Duplex Pipe Containers.
    class Duplex {
        //  PROPERTIES  //

        Simplex m_input = Invalid();   // Input pipe.
        Simplex m_output = Invalid();  // Output pipe.

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs an invalid pipe pair.
        constexpr Duplex() = default;

        /**
         * @brief Constructs a duplex pipe.
         * @param inherit               Creation flag.
         */
        constexpr Duplex(Atomic inherit) : Duplex(m_create(inherit)) {}

        /**
         * @brief Receives ownership of the given pipes.
         * @param input                 Input pipe.
         * @param output                Output pipe.
         */
        constexpr Duplex(Handle input, Handle output) : m_input(input), m_output(output) {}

        /// @brief Do not allow copy-construction.
        constexpr Duplex(const Duplex&) = delete;

        /// @brief Allow moving duplexed pipes.
        constexpr Duplex(Duplex&& other) : Duplex(other.m_input.detach(), other.m_output.detach()) {}

        /// @brief Ensures loose pipes are all closed up.
        constexpr ~Duplex() { close(); }

        //  OPERATOR METHODS  //

        inline constexpr Duplex& operator=(const Duplex&) = delete;
        inline constexpr Duplex& operator=(Duplex&& other) {
            m_input = other.m_input.detach();
            m_output = other.m_output.detach();
            return *this;  // return base ref
        }

        //  PUBLIC METHODS  //

        inline constexpr Simplex* input() noexcept { return &m_input; }
        inline constexpr const Simplex* input() const noexcept { return &m_input; }

        inline constexpr Simplex* output() noexcept { return &m_output; }
        inline constexpr const Simplex* output() const noexcept { return &m_output; }

        inline constexpr void close() noexcept { m_input.close(), m_output.close(); }
        inline constexpr void detach() noexcept { m_input.detach(), m_output.detach(); }

        /// @brief Denotes if both handles are the same.
        inline constexpr bool mirrored() const noexcept { return m_input.handle() == m_output.handle(); }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles creating duplex pipes.
         * @param inherit               Creation flag.
         */
        static Duplex m_create(Atomic inherit) noexcept;
    };

}  // namespace XPC::Pipe

#endif
