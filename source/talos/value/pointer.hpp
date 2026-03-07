#ifndef _TALOS_VALUE_POINTER_HPP
#define _TALOS_VALUE_POINTER_HPP

/// Talos Includes
#include "talos/forward/async.hpp"
#include "talos/forward/function.hpp"
#include "talos/forward/handle.hpp"
#include "talos/forward/iterable.hpp"
#include "talos/forward/monad.hpp"
#include "talos/forward/number.hpp"
#include "talos/forward/object.hpp"
#include "talos/forward/runtime.hpp"
#include "talos/forward/string.hpp"
#include "talos/value/feedback.hpp"

/**
 *
 * The tagged-pointer scheme supports the following value types:
 *
 * DDDDDDDD DDDDDDDD DDDDDDDD DDDDDDDD DDDDDDDD DDDDDDDD DDDDDDDD DDDDDDD 0     NUM
 * xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxB xxxx 0001     BIT
 * SSSSSSSS SSSSSSSS SSSSSSSS SSSSSSSS SSSSSSSS SSSSSSSS SSSSSSSS SSSS 0011     SYM
 * SSSSSSSS SSSSSSSS SSSSSSSS SSSSSSSS SSSSSSSS SSSSSSSS SSSSSSSS LLLL 0101     SSTR
 * xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx EEEE 0111     VOID
 * xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxx 1001     OBJ (JUNIOR)
 * xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxx 1011     OBJ (SENIOR)
 * xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxx 1101     -
 * xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxx 1111     -
 *
 * This scheme supports immediate 63-bit integers, which are denoted by a LSB of 0.
 * Values that then have a LSB of 1 are either pointers or other immediate values. The
 * other immediate values available are:
 *
 *  NUM  |  63-bit IEEE 754 double-precision floats. The last bit of the mantissa is
 *          trimmed off when encoding, resulting in a small loss of precision, but no
 *          loss in range at all.
 *
 *  SYM  |  Unique symbol (hash-value).
 *  OBJ  |  Pointer to heap-allocated objects.
 *  BIT  |  Booleans encoded as either a true/false value.
 *  SSTR |  Small strings encoded into 7-bytes (can only be valid UTF-8).
 *  VOID |  Singleton "null" type. Can also carry a 1-byte feedback code.
 *
 */

//  X-MACROS  //

/// @brief Available pointer tags.
#define XX_POINTER_KINDS(X) \
    X(NUM, 0b0000)          \
    X(BIT, 0b0001)          \
    X(SYM, 0b0011)          \
    X(SSTR, 0b0101)         \
    X(VOID, 0b0111)         \
                            \
    X(JUN, OBJ | 0b0000)    \
    X(SEN, OBJ | 0b0010)

//  NAMESPACES  //

namespace Talos::Pointer {

    /// @brief Underlying Pointer Typing.
    using Underlying = uintptr_t;

    /// @brief Underlying numeric typing.
    using Numeric = $_ARCH_TYPED(double, float);

    /// @brief Underlying integral typing.
    using Integral = $_ARCH_TYPED(int64_t, int32_t);

    /// @brief Validate the incoming pointer numeric.
    static_assert(sizeof(Numeric) == sizeof(Underlying));

    /// @brief Associated pointer kinds.
    enum class Kind : uint8_t { $_XX_ENUM_VALUE(OBJ, 0b1001) XX_POINTER_KINDS($_XX_ENUM_VALUE) };

    /// @brief Available mask values.
    namespace Mask {
        static constexpr Underlying NUM = 0x01;   // Masks number values.
        static constexpr Underlying IMM = 0x0F;   // Masks immediates.
        static constexpr Underlying SLEN = 0xF0;  // Masks string-length.
        static constexpr Underlying LAST = 0xFF;  // Masks last byte.
    };  // namespace Mask

    /// @brief Available shift values.
    namespace Shift {
        static constexpr int32_t NUM = 1;  // Number decode shift.
        static constexpr int32_t OBJ = 1;  // Object flag shift.
        static constexpr int32_t FBK = 4;  // Void/Error shift.
        static constexpr int32_t SYM = 4;  // Symbol decode shift.
        static constexpr int32_t LEN = 4;  // Length decode shift.
        static constexpr int32_t BIT = 8;  // Boolean decode shift.
        static constexpr int32_t STR = 8;  // Small string decode shift.
    };  // namespace Shift

    /// @brief Expected value alignments.
    namespace Alignment {
        static constexpr size_t VALUE = sizeof(Underlying);     // Size of pointer.
        static constexpr size_t OBJECT = 1 + (UINT8_MAX >> 4);  // Aligned to half-byte.
    };  // namespace Alignment

    /// @brief Tagged Pointer Wrapper.
    class Traits : public $::Printable {
        //  PROPERTIES  //

        /// @brief Associated tag value.
        Underlying m_value = static_cast<Underlying>(Kind::VOID);

       public:
        //  CONSTRUCTORS  //

        /// @brief Defaults to a "void" pointer.
        constexpr Traits() = default;

        /**
         * @brief Constructs from another pointer.
         * @param pointer                   Value to assign.
         */
        constexpr Traits(Underlying pointer) : m_value(pointer) {}

        /**
         * @brief Constructs a pointer value.
         * @param kind                      Kind to assign.
         */
        constexpr Traits(Kind kind) : m_value(static_cast<Underlying>(kind)) {}

        //  OPERATOR METHODS  //

        /// @brief Allow conversion to underlying typing.
        inline constexpr operator Underlying() const noexcept { return m_value; }

        inline constexpr bool operator==(const Traits& other) const noexcept { return m_value == other.m_value; }
        inline constexpr bool operator!=(const Traits& other) const noexcept { return m_value != other.m_value; }

        //  PUBLIC METHODS  //

        /// @brief Denotes if the pointer is in an "okay" state.
        inline constexpr bool okay() const noexcept { return feedback() < Value::Feedback::EXCEPTION_THROWN; }
        inline constexpr bool sentinel() const noexcept { return feedback() == Value::Feedback::ITERATOR_SENTINEL; }
        inline constexpr bool null() const noexcept { return is<Kind::OBJ>() && (m_value & ~Pointer::Mask::IMM) == 0; }

        /// @brief Gets the associated feedback state.
        inline constexpr Value::Feedback feedback() const noexcept {
            if (!is<Kind::VOID>()) return Value::Feedback::ALL_OKAY;
            return static_cast<Value::Feedback>(m_value >> Shift::FBK);
        }

        /// @brief Gets the underlying tag value.
        inline constexpr Kind kind() const noexcept {
            return static_cast<Kind>(m_value & (m_value % 2 ? Mask::IMM : Mask::NUM));
        }

        /// @brief Checks for associated tags.
        template <Kind... As>
        inline constexpr bool is() const noexcept {
            return ((kind() == As) || ...);
        }

        /// @brief Gets the associated pointer label.
        inline constexpr $::String::View label() const noexcept {
#define X(N, ...) \
    case Kind::N: return #N;
            switch (kind()) { XX_POINTER_KINDS(X) default : return "UNK"; }
#undef X
        }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles printing pointers.
         * @param os                        Output stream.
         * @param self                      Pointer value.
         */
        static inline void m_print($::Stream::Output& os, const Traits& self) {
            os << fmt::format("0x{0:0X} ({1})", self.m_value, self.label());
        }
    };

}  // namespace Talos::Pointer

//  UNDEFINES  //

#undef XX_POINTER_TAGS

#endif
