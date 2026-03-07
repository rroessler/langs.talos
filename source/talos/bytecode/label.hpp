#ifndef _TALOS_BYTECODE_LABEL_HPP
#define _TALOS_BYTECODE_LABEL_HPP

/// Talos Modules
#include "talos/engine/operand.hpp"

namespace Talos::Bytecode {

    /// @brief Explicit Index Typing.
    struct Index : public Engine::Operand<2>, public $::Strong::Unit<uint16_t, Index>, public $::Printable {
        //  TYPEDEFS  //

        /// @brief The encoded typing.
        using Encoded = $::Strong::Infer<Index>::Underlying;

        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructors.
        using Unit::Unit;

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying encoded value.
        inline constexpr Encoded encode() const noexcept { return m_underlying(); }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles printing index values.
         * @param os                    Output stream.
         * @param self                  Index value.
         */
        static inline void m_print($::Stream::Output& os, const Index& self) { os << '[' << self.encode() << ']'; }
    };

    /// @brief Explicit Label Typing.
    struct Label : public Index {
        //  TYPEDEFS  //

        /// @brief Unresolved label patch.
        using Patch = std::pair<Index, Label>;

        /// @brief The encoded label typing.
        using Encoded = $::Strong::Infer<Label>::Underlying;

        /// @brief Placed labels container.
        using Placed = $::Map<Label, Encoded>;

        /// @brief Unresolved labels container.
        using Unresolved = $::Map<Encoded, Patch>;

        //  CONSTRUCTORS  //

        /// @brief Inherit the base constructors.
        using Index::Index;

        /**
         * @brief Casts indicies to labels.
         * @param index                 Index to cast.
         */
        constexpr Label(const Index& index) : Index(index) {}
        constexpr Label(Index&& index) : Index(std::move(index)) {}

        //  PUBLIC METHODS  //

        /// @brief Gets the underlying encoded value.
        inline constexpr Encoded encode() const noexcept { return m_underlying(); }

       protected:
        //  PRIVATE METHODS  //

        /**
         * @brief Handles printing label values.
         * @param os                    Output stream.
         * @param self                  Label value.
         */
        static inline void m_print($::Stream::Output& os, const Label& self) { os << ".L" << self.encode(); }
    };

}  // namespace Talos::Bytecode

//  SPECIALIZATIONS  //

template <>
struct ankerl::unordered_dense::hash<Talos::Bytecode::Index> {
    using is_avalanching = void;  // declare that this is not avalanchable
    $_NODISCARD uint64_t operator()(const Talos::Bytecode::Index& index) const noexcept { return index.encode(); }
};

template <>
struct ankerl::unordered_dense::hash<Talos::Bytecode::Label> {
    using is_avalanching = void;  // declare that this is not avalanchable
    $_NODISCARD uint64_t operator()(const Talos::Bytecode::Label& label) const noexcept { return label.encode(); }
};

#endif
