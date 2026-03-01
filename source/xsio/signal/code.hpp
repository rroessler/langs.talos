#ifndef _XSIO_SIGNAL_CODE_HPP
#define _XSIO_SIGNAL_CODE_HPP

/// XSIO Modules
#include "xsio/forward/signal.hpp"

//  X-MACROS  //

/// @brief All available symbolic signals.
#define XSIO_XX_SIGNALS_LIST(X)            \
    X(HUP, 1, "Terminal Hung Up")          \
    X(INT, 2, "Keyboard Interrupt")        \
    X(QUIT, 3, "Quit Request")             \
    X(ILL, 4, "Illegal Instruction")       \
    X(TRAP, 5, "Trace of Breakpoint Trap") \
    X(ABRT, 6, "Abort Request")            \
    X(BUS, 7, "Bad Memory Access")         \
    X(FPE, 8, "Floating Point Exception")  \
    X(KILL, 9, "Forced Quit Request")      \
    X(USR1, 10, "User Defined Signal 1")   \
    X(SEGV, 11, "Segmentation Fault")      \
    X(USR2, 12, "User Defined Signal 2")   \
    X(PIPE, 13, "Broken Pipe")             \
    X(ALRM, 14, "Timer Expired")           \
    X(TERM, 15, "Polite Quit Request")

//  NAMESPACES  //

namespace XSIO::Signal {

    /// @brief Underlying signal values.
    using Underlying = int32_t;

    /// @brief Signal set typing.
    using Set = $::Set<Underlying>;

    /// @brief The Symbolic Signal Codes.
    $_XX_ENUM_CLASS(Symbolic, Underlying, XSIO_XX_SIGNALS_LIST, UNK = -1);

    /// @brief For unknown signal values.
    static inline constexpr Symbolic Unknown() { return Symbolic::UNK; }

    /// @brief Underlying code value.
    class Code : public $::Printable {
        //  PROPERTIES  //

        /// @brief Underlying code-value.
        Symbolic m_value = Symbolic::UNK;

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs an "OKAY" value.
        explicit constexpr Code() = default;

        /**
         * @brief Constructs a signal instance.
         * @param value                 Value to assign.
         */
        constexpr Code(Symbolic value) : m_value(value) {}

        /**
         * @brief Handles constructing a named signal.
         * @param name                  Name of signal.
         */
        constexpr Code(const $::String::View& name) : m_value(Unknown()) {
#define X(N, ...) \
    case XH::FNV::U32("SIG" #N): m_value = Symbolic::N; break;
            switch (XH::FNV::U32(name)) { XSIO_XX_SIGNALS_LIST(X) }
#undef X
        }

        //  PUBLIC METHODS  //

        /// @brief Gets the associated name.
        inline constexpr $::String::View name() const noexcept {
#define X(N, ...) \
    case Symbolic::N: return "SIG" #N;
            switch (m_value) { XSIO_XX_SIGNALS_LIST(X) default : return "SIGUNK"; }
#undef X
        }

        /// @brief Gets the underlying code value.
        inline constexpr Symbolic value() const noexcept { return m_value; }

        /// @brief Gets the underlying numeric value.
        inline constexpr Underlying underlying() const noexcept { return static_cast<Underlying>(m_value); }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles printing signals.
         * @param os                    Output stream.
         * @param self                  Signal code.
         */
        static inline void m_print($::Stream::Output& os, const Code& self) { os << self.name(); }
    };

}  // namespace XSIO::Signal

#endif
