#ifndef _TALOS_ENGINE_REGISTER_HPP
#define _TALOS_ENGINE_REGISTER_HPP

/// Talos Modules
#include "talos/engine/operand.hpp"

namespace Talos::Engine {

    /// @brief Register Typing.
    struct Register : public Operand<2>, public $::Strong::Unit<uint16_t, Register>, public $::Printable {
        //  TYPEDEFS  //

        class List;    // Register list value.
        struct Span;   // Register list view.
        class Scoped;  // Short-lived register.

        /// @brief Encoded register typing.
        using Encoded = $::Strong::Infer<Unit>::Underlying;

        //  CONSTRUCTORS  //

        /// @brief Inherit the baseline constructors.
        using Unit::Unit;

        /// @brief Constructs an empty register value.
        constexpr Register() : Unit(m_maximum()) {}

        //  PUBLIC METHODS  //

        inline constexpr Encoded encode() const noexcept { return m_underlying(); }
        inline constexpr bool nowhere() const noexcept { return m_underlying() == m_maximum(); }
        inline constexpr bool accumulator() const noexcept { return m_underlying() == m_minimum(); }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles printing register values.
         * @param os                    Output stream.
         * @param self                  Register instance.
         */
        static inline void m_print($::Stream::Output& os, const Register& self) {
            if (self.nowhere()) os << "RN";
            else if (self.accumulator()) os << "RA";
            else os << 'R' << self.m_underlying();
        }
    };

    /// @brief Accumulator Register Instance.
    struct Accumulator : public Register {
        //  CONSTRUCTORS  //

        /// @brief Only allow baseline construction with the accumulator value.
        constexpr Accumulator() : Register(m_minimum()) {}
    };

    /// @brief Temporary Register Instance.
    class Register::Scoped : public Register {
        //  PROPERTIES  //

        /// @brief Underlying allocator reference.
        Bytecode::Allocator* m_allocator = nullptr;

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted temporary register.
        using Register::Register;

        /**
         * @brief Constructs a temporary register.
         * @param allocator                 Allocator reference.
         */
        Scoped(Bytecode::Allocator* allocator);

        /// @brief Removes the volatile register.
        ~Scoped();
    };

    /// @brief Register List View.
    struct Register::Span : public Operand<3>, public $::Printable {
        //  TYPEDEFS  //

        /// @brief The encoded list typing.
        using Encoded = uint32_t;

       protected:
        //  PRIVATE METHODS  //

        /// @brief Total register count.
        uint8_t m_count = 0;

        /// @brief The first register attached.
        Register::Encoded m_first = m_maximum();

        static constexpr Encoded m_shift = 16;     // Shift constant.
        static constexpr Encoded m_mask = 0xFFFF;  // Mask constant.

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted span.
        constexpr Span() = default;

        /**
         * @brief Constructs a span from an encoded value.
         * @param encoded               Encoded span value.
         */
        constexpr Span(Encoded encoded) : Span(encoded & m_mask, encoded >> m_shift) {}

        /**
         * @brief Constructs a span.
         * @param first                 Initial value.
         * @param count                 Total span count.
         */
        constexpr Span(Register::Encoded first, uint8_t count) : m_count(count), m_first(first) {}

        //  PUBLIC METHODS  //

        inline constexpr bool empty() const noexcept { return m_count == 0; }
        inline constexpr uint8_t count() const noexcept { return m_count; }

        inline constexpr Register first() const noexcept { return m_count ? m_first : UINT16_MAX; }
        inline constexpr Register last() const noexcept { return m_count ? m_first + (m_count - 1) : UINT16_MAX; }
        inline constexpr Encoded encode() const noexcept { return m_first | (m_count << m_shift); }

        /**
         * @brief Handles slicing spans.
         * @param offset                Leading offset.
         */
        inline constexpr Span slice(uint8_t offset = 0) const noexcept {
            if (empty() || offset > m_count) return Span();
            return Span(m_first + offset, m_count - offset);
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Prints a register span.
         * @param os                    Output stream.
         * @param self                  Register span.
         */
        static inline void m_print($::Stream::Output& os, const Span& self) {
            if (self.m_count == 0) os << "()";  // empty
            else os << self.first() << '-' << self.last();
        }
    };

    /// @brief Register List Value.
    class Register::List : public Span {
        //  PROPERTIES  //

        /// @brief Underlying allocator reference.
        Bytecode::Allocator* m_allocator;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs a register-list.
         * @param allocator             Register allocator.
         */
        List(Bytecode::Allocator* allocator = nullptr);

        /// @brief Ensures lists are freed on deletion.
        ~List();

        //  PUBLIC METHODS  //

        /// @brief Grows the list instance.
        Register grow();
    };

}  // namespace Talos::Engine

#endif
