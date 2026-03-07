#ifndef _TALOS_BYTECODE_METADATA_HPP
#define _TALOS_BYTECODE_METADATA_HPP

/// Talos Modules
#include "talos/function/info.hpp"
#include "talos/linker/arena.hpp"
#include "talos/module/metadata.hpp"
#include "talos/runtime/isolate.hpp"

namespace Talos::Module {

    /// @brief Constructs a set of bytecode metadata.
    template <>
    class Metadata::Attributes<Phase::COMPILED> : public Metadata {
        //  PROPERTIES  //

        /// @brief Associated output arena.
        $::Ptr::Unique<Linker::Arena> m_arena = $::New().unique<Linker::Arena>();

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a set of exports.
        explicit Attributes() = default;

        //  PUBLIC METHODS  //

        inline constexpr $::Ptr::Unique<Linker::Arena>& arena() noexcept { return m_arena; }
        inline constexpr const Linker::Arena* arena() const noexcept { return m_arena.get(); }
    };

}  // namespace Talos::Module

#endif
