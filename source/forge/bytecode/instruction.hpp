#ifndef _FORGE_BYTECODE_INSTRUCTION_HPP
#define _FORGE_BYTECODE_INSTRUCTION_HPP

/// Vendor Modules
#include <xlsp/xlsp.hpp>

/// Forge Modules
#include "forge/bytecode/operands.hpp"
#include "forge/bytecode/syllable.hpp"

//  MACROS  //

/// @brief Helper for constructing bytecode instructions.
#define FORGE_MM_BIR(S, ...) ::Forge::Bytecode::Qualified<::Forge::Bytecode::Syllable::S>(__VA_ARGS__)

//  NAMESPACES  //

namespace Forge::Bytecode {

    /// @brief Bytecode View Container.
    template <Syllable S>
    class Qualified;

    /// @brief Base Instruction Container.
    struct Instruction : public $::Printable {
        //  TYPEDEFS  //

        /// @brief Underlying encoding type.
        using Encoded = uint64_t;

       protected:
        //  PROPERTIES  //

        /// @brief The underlying encoded value.
        Encoded m_underlying;

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Constructs an instruction.
         * @param syllable              Base syllable.
         */
        constexpr Instruction() : Instruction(Syllable::EXEC_NOOP) {}
        constexpr Instruction(Encoded encoded) : m_underlying(encoded) {}
        constexpr Instruction(Syllable syllable) : m_underlying(static_cast<Encoded>(syllable)) {}

        //  PUBLIC METHODS  //

        inline constexpr Encoded encode() const noexcept { return m_underlying; }
        inline constexpr Syllable syllable() const noexcept { return static_cast<Syllable>(m_underlying & 0xFF); }

        /// @brief Converts the instruction to a valid view.
        template <Syllable S>
        inline constexpr Qualified<S>* cast() noexcept {
            return $_ASSERT(syllable() == S), static_cast<Qualified<S>*>(this);
        }

        /// @brief Converts the instruction to a valid view.
        template <Syllable S>
        inline constexpr const Qualified<S>* cast() const noexcept {
            return $_ASSERT(syllable() == S), static_cast<const Qualified<S>*>(this);
        }

        /// @brief Gets the associated instruction name.
        inline constexpr $::String::View name() const noexcept {
            switch (syllable()) {
#define FORGE_XX_SYLLABLE_BASE(N, ...) \
    case Syllable::N: return #N;
#include "forge/bytecode/_defines/syllables.def"
                default: return "MISC_UNK";
            }
        }

        /// @brief Denotes if an incoming target branches.
        inline constexpr bool branches() const noexcept {
            switch (syllable()) {
#define FORGE_XX_SYLLABLE_JUMP(N, ...) \
    case Syllable::N: return true;
#include "forge/bytecode/_defines/syllables.def"
                default: return false;
            }
        }

        /// @brief Denotes if this is a terminating instruction.
        inline constexpr bool terminates() const noexcept {
            switch (syllable()) {
                case Syllable::EXEC_ABORT: $_FALLTHROUGH;
                case Syllable::EXEC_PANIC: $_FALLTHROUGH;
                case Syllable::EXEC_RETURN: return true;
                default: return false;
            }
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles printing instructions.
         * @param os                    Output stream.
         * @param self                  Instruction value.
         */
        static void m_print($::Stream::Output& os, const Instruction& self);
    };

    /// @brief Qualified Instruction View.
    template <Syllable S>
    class Qualified : public Instruction {
        //  TYPEDEFS  //

        /// @brief Arguments Typing View.
        template <Syllable>
        struct Arguments;

        /// @brief Allow instructions internal access.
        friend struct Instruction;

#define FORGE_XX_SYLLABLE_BASE(N, ...) \
    template <>                        \
    struct Arguments<Syllable::N> : public Operands<__VA_ARGS__> {};
#include "forge/bytecode/_defines/syllables.def"

       public:
        //  CONSTRUCTORS  //

        /**
         * @brief Handles constructing a qualified instruction.
         * @param operands              Operands to assign.
         */
        template <class... As>
        constexpr Qualified(As&&... operands) : Instruction(S) {
            m_unpack(std::make_index_sequence<sizeof...(As)>(), std::forward<As>(operands)...);
        }

        //  PUBLIC METHODS  //

        /// @brief Gets an instruction operand at the given index.
        template <size_t I>
        inline constexpr auto get() const noexcept {
            using T = Arguments<S>::template Element<I>;
            auto [offset, mask] = Arguments<S>::template traits<I>();
            return T((m_underlying >> (sizeof(Syllable) + offset) * 8) & mask);
        }

        /**
         * @brief Sets an operand at the given index.
         * @param value                 Value to assign.
         */
        template <size_t I>
        inline constexpr void set(const Arguments<S>::template Element<I>& value) {
            auto [offset, mask] = Arguments<S>::template traits<I>();  // prepare traits
            m_underlying |= (value.encode() & mask) << (sizeof(Syllable) + offset) * 8;
        }

       private:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles unpacking multiple operands to be set.
         * @param operands              Operands to unpack.
         */
        template <class... As, size_t... Is>
        inline constexpr void m_unpack(std::index_sequence<Is...>, As&&... operands) {
            ((set<Is>(operands)), ...);  // unpack all the incoming operands
        }

        /**
         * @brief Handles printing the qualified instruction.
         * @param os                    Output stream.
         */
        template <size_t... Is>
        inline constexpr void m_print($::Stream::Output& os, std::index_sequence<Is...>) const noexcept {
            (..., (os << (Is == 0 ? " " : ", ") << get<Is>()));
        }

        /**
         * @brief Handles printing the qualified instruction.
         * @param os                    Output stream.
         */
        inline constexpr void m_print($::Stream::Output& os) const noexcept { m_print(os, Arguments<S>::sequence()); }
    };

}  // namespace Forge::Bytecode

#endif
