#ifndef _FORGE_BYTECODE_METADATA_HPP
#define _FORGE_BYTECODE_METADATA_HPP

/// Forge Modules
#include "forge/function/info.hpp"
#include "forge/linker/arena.hpp"
#include "forge/module/metadata.hpp"
#include "forge/runtime/isolate.hpp"

namespace Forge::Module {

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

}  // namespace Forge::Module

#endif
