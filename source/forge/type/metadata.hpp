#ifndef _FORGE_TYPE_METADATA_HPP
#define _FORGE_TYPE_METADATA_HPP

/// Forge Modules
#include "forge/module/metadata.hpp"
#include "forge/type/context.hpp"

namespace Forge::Module {

    /// @brief Constructs a set of typed metadata.
    template <>
    class Metadata::Attributes<Phase::TYPED> : public Metadata {
        //  PROPERTIES  //

        /// @brief Construct the underlying type-context.
        $::Ptr::Unique<Type::Context> m_context = $::New().unique<Type::Context>();

       public:
        //  CONSTRUCTORS  //

        /// @brief Constructs a set of exports.
        explicit Attributes() = default;

        //  PUBLIC METHODS  //

        inline constexpr $::Ptr::Unique<Type::Context>& context() noexcept { return m_context; }
        inline constexpr const Type::Context* context() const noexcept { return m_context.get(); }
    };

}  // namespace Forge::Module

#endif
