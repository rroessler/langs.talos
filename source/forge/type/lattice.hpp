#ifndef _FORGE_TYPE_LATTICE_HPP
#define _FORGE_TYPE_LATTICE_HPP

/// Forge Modules
#include "forge/forward/type.hpp"

namespace Forge::Type {

    /// @brief Available Type Facts.
    enum class Fact : uint32_t {
        BOT_TYPE = 0,

        NUM_TYPE = 1 << 0,
        BIT_TYPE = 1 << 1,
        STR_TYPE = 1 << 2,
        NIL_TYPE = 1 << 3,
        SYM_TYPE = 1 << 4,
        OBJ_TYPE = 1 << 5,
        FUN_TYPE = 1 << 6,

        ANY_TYPE = UINT16_MAX,

        IS_TRUTHY = 1 << 16,
        IS_FALSEY = 1 << 17,

        NUM_ANY = NUM_TYPE,
        NUM_SOME = NUM_ANY | IS_TRUTHY,
        NUM_ZERO = NUM_ANY | IS_FALSEY,

        BIT_ANY = BIT_TYPE,
        BIT_TRUE = BIT_ANY | IS_TRUTHY,
        BIT_FALSE = BIT_ANY | IS_FALSEY,

        STR_ANY = STR_TYPE,
        STR_SOME = STR_ANY | IS_TRUTHY,
        STR_EMPTY = STR_ANY | IS_FALSEY,

        NIL_ANY = NIL_TYPE | IS_FALSEY,
        SYM_ANY = SYM_TYPE | IS_TRUTHY,
        OBJ_ANY = OBJ_TYPE | IS_TRUTHY,
        FUN_ANY = FUN_TYPE | IS_TRUTHY,
    };

    /// @brief Type Lattice Container.
    class Lattice : public $::Printable {
        //  TYPEDEFS  //

        /// @brief The underlying facts typing.
        using Underlying = std::underlying_type_t<Fact>;

        //  PROPERTIES  //

        /// @brief The underlying bitset value.
        Underlying m_bitset = static_cast<Underlying>(Fact::BOT_TYPE);

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a defaulted lattice.
        constexpr Lattice() = default;

        /**
         * @brief Constructs a type-lattice from a type.
         * @param type                  Type to resolve.
         */
        explicit Lattice(const Erased& type);

        /**
         * @brief Constructs a lattice of facts.
         * @param facts                 Facts to bind.
         */
        template <std::convertible_to<Underlying>... Fs>
        constexpr Lattice(Fs&&... facts) : m_bitset((facts || ...)) {}

        /**
         * @brief Constructs a lattice of facts.
         * @param facts                 Facts to bind.
         */
        template <std::convertible_to<Fact>... Fs>
        constexpr Lattice(Fs&&... facts) : m_bitset((static_cast<Underlying>(facts) || ...)) {}

        //  OPERATOR METHODS  //

        /// @brief Allows merging lattices together.
        inline constexpr Lattice operator|(const Lattice& other) const noexcept { return join(other); }

        //  PUBLIC METHODS  //

        /// @brief Tests if we have a top/bottom typing.
        inline constexpr bool bottom() const noexcept { return strictly(Fact::BOT_TYPE); }
        inline constexpr bool dynamic() const noexcept { return strictly(Fact::ANY_TYPE); }

        /// @brief Gets the associated truthy states.
        inline constexpr bool truthy() const noexcept { return static_cast<bool>(m_truthiness()); }
        inline constexpr bool falsey() const noexcept { return static_cast<bool>(!m_truthiness()); }

        /**
         * @brief Checks against subtyping.
         * @param fact                  Fact to check.
         */
        inline constexpr bool test(Fact fact) const noexcept { return test(static_cast<Underlying>(fact)); }
        inline constexpr bool test(Underlying fact) const noexcept { return (m_bitset & fact) == fact; }

        /**
         * @brief Checks against strict subtyping.
         * @param fact                  Fact to check.
         */
        inline constexpr bool strictly(Fact fact) const noexcept { return strictly(static_cast<Underlying>(fact)); }
        inline constexpr bool strictly(Underlying fact) const noexcept { return m_type() == fact; }

        /**
         * @brief Joins two lattice values together.
         * @param other                 Other lattice to join.
         */
        inline constexpr Lattice join(const Lattice& other) const noexcept {
            // if equal, then do not change anything
            if (m_bitset == other.m_bitset) return m_bitset;

            // prepare the merged typing to be returned
            auto merged = m_bitset | other.m_bitset;

            // check if the underlying truthiness values are exact
            auto similar = m_truthiness() == other.m_truthiness();
            return bool(similar) ? merged : (merged & m_mask());
        }

       protected:
        //  PRIVATE METHODS  //

        /// @brief Gets the underlying truthiness.
        inline constexpr $::Ternary m_truthiness() const noexcept {
            auto truthy = test(Fact::IS_TRUTHY);  // get the truthy
            auto falsey = test(Fact::IS_FALSEY);  // and falsey facts
            return truthy == falsey ? $::Unknown() : $::Ternary(truthy);
        }

        /// @brief Gets the underlying strict-type.
        inline constexpr Underlying m_type() const noexcept { return m_bitset & m_mask(); }

        /// @brief Gets the underlying mask-type.
        inline constexpr Underlying m_mask() const noexcept { return static_cast<Underlying>(Fact::ANY_TYPE); }

        /**
         * @brief Handles printing lattices.
         * @param os                    Output stream.
         * @param self                  Lattice instance.
         */
        static inline void m_print($::Stream::Output& os, const Lattice& self) {
            os << fmt::format("{0:032B}", self.m_bitset);
        }
    };

}  // namespace Forge::Type

#endif
